/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        SharedUtil.HashMap.h
*  PURPOSE:
*  DEVELOPERS:  
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/
#pragma once

#if WITH_ALLOC_TRACKING
    #define CHashMap CMap
#else

#include <unordered_map>
#include <functional>

namespace SharedUtil
{

    ////////////////////////////////////////////////
    //
    // Using hash_map
    //
    template < class K, class V >
    class CHashMap : public std::unordered_map < K, V >
    {
    public:
    };


    ////////////////////////////////////////////////
    //
    // CHashMap helpers
    // 

    // Remove key from collection
    template < class T, class V, class T2 >
    bool MapRemove ( CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::iterator it = collection.find ( key );
        if ( it == collection.end () )
            return false;
        collection.erase ( it );
        return true;
    }

    // Find value in collection
    template < class T, class V, class T2 >
    V* MapFind ( CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::iterator it = collection.find ( key );
        if ( it == collection.end () )
            return NULL;
        return &it->second;
    }

    // Find value in const collection
    template < class T, class V, class T2 >
    const V* MapFind ( const CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::const_iterator it = collection.find ( key );
        if ( it == collection.end () )
            return NULL;
        return &it->second;
    }

    // Find value reference in collection
    template < class T, class V, class T2 >
    V MapFindRef ( CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::iterator it = collection.find ( key );
        if ( it == collection.end () )
            return NULL;
        return it->second;
    }

    // Find value reference in const collection
    template < class T, class V, class T2 >
    const V MapFindRef ( const CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::const_iterator it = collection.find ( key );
        if ( it == collection.end () )
            return NULL;
        return it->second;
    }

    // Find or add a value in collection
    template < class T, class V, class T2 >
    V& MapGet ( CHashMap < T, V >& collection, const T2& key )
    {
        typename CHashMap < T, V > ::iterator it = collection.find ( key );
        if ( it == collection.end () )
        {
            collection[key] = V ();
            it = collection.find ( key );
        }
        return it->second;
    }
}


// Calculate a hash value for SString
template<>
struct std::hash<SString>
{
    size_t operator()(const SString& str) const
    {
        return std::hash<std::string>()(str);
    }
};

#if defined(WIN32)
inline size_t hash_value ( const SString& strString ) // Required for sparsehash
{
    std::hash<std::string> hashFunction;
    return hashFunction ( strString );
}
#elif defined(__GNUC__) && (__GNUC__ >= 3)
namespace __gnu_cxx
{
    template<>
    struct hash < SString >
    {
        size_t operator () ( const SString& strString ) const
        {
            return __stl_hash_string ( strString );
        }
    };
}
#endif

#endif  // WITH_ALLOC_TRACKING
