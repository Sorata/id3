#include <iterator>
#include "id3v2.h"

class ID3tag {
public:
    class iterator;

    ID3tag(const char* fname);
    ~ID3tag();

    unsigned long size();

    iterator begin();
    iterator end();

private:
    unsigned long tagsize;
    void* buf;
};

class ID3tag::iterator
    : public std::iterator<std::forward_iterator_tag,_ID3FRAME> {
    friend class ID3tag;
public:
    iterator() : stat(false) { }

    iterator& operator++()
    { stat = ID3_frame(f); return *this; }

    iterator  operator++(int)
    { iterator t = *this; ++(*this); return t; }

    ID3FRAME& operator*()
    { return f; }

    _ID3FRAME* operator->()
    { return f; }

    bool operator==(const iterator& other) const
    { return stat == other.stat && (!stat || f->data == other.f->data); }

    bool operator!=(const iterator& other) const
    { return !(*this == other); }

    operator bool()
    { return stat; }

private:
    ID3FRAME f;
    bool stat;

    iterator(void* buf)
    { ID3_start(f, buf); stat = ID3_frame(f); }
};

inline ID3tag::iterator ID3tag::begin()
{
    if(buf)
        return iterator(buf);
    else
        return end();
}

inline ID3tag::iterator ID3tag::end()
{ return iterator(); }

inline ID3tag::ID3tag(const char* fname)
{ buf = ID3_readf(fname, &tagsize); }

inline ID3tag::~ID3tag()
{ ID3_free(buf); }

inline unsigned long ID3tag::size()
{ return tagsize; }
