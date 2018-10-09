#include <sys/time.h>

#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <iostream>
#include <string>

#include "http_header_switch.hpp"

using match::http_header::weekday;
using namespace std::literals;

std::unordered_map< std::string, int64_t > score_umap = {
    { "Accept-Charset" ,              9 },
    { "Accept-Encoding" ,             98 },
    { "Content-Encoding" ,            987 },
    { "Content-Length" ,              9876 },
    { "Host" ,                        98765 },
    { "If-Unmodified-Since" ,         987654 },
    { "Keep-Alive" ,                  987655443 },
    { "Referer" ,                     10 },
    { "Upgrade-Insecure-Requests" ,   11 },
    { "User-Agent" ,                  13 },
};

int64_t score_it_um( std::string_view in )
{
    int64_t res = 0;

    auto it = score_umap.find( std::string( in ) );
    if ( it == score_umap.end() )
        res -= 200;
    else
        res += it->second;

    return res;
}

std::map< std::string, int64_t > score_map = {
    { "Accept-Charset" ,              9 },
    { "Accept-Encoding" ,             98 },
    { "Content-Encoding" ,            987 },
    { "Content-Length" ,              9876 },
    { "Host" ,                        98765 },
    { "If-Unmodified-Since" ,         987654 },
    { "Keep-Alive" ,                  987655443 },
    { "Referer" ,                     10 },
    { "Upgrade-Insecure-Requests" ,   11 },
    { "User-Agent" ,                  13 },
};

int64_t score_it_map( std::string_view in )
{
    int64_t res = 0;

    auto it = score_map.find( std::string( in ) );
    if ( it == score_map.end() )
        res -= 200;
    else
        res += it->second;

    return res;
}

std::vector< std::pair< std::string_view, int64_t > > sorted_vec = {
    { "Accept-Charset"sv ,              9 },
    { "Accept-Encoding"sv ,             98 },
    { "Content-Encoding"sv ,            987 },
    { "Content-Length"sv ,              9876 },
    { "Host"sv ,                        98765 },
    { "If-Unmodified-Since"sv ,         987654 },
    { "Keep-Alive"sv ,                  987655443 },
    { "Referer"sv ,                     10 },
    { "Upgrade-Insecure-Requests"sv ,   11 },
    { "User-Agent"sv ,                  13 },
};

int64_t score_it_sorted_vector( std::string_view in )
{
    int64_t res = 0;

    auto it = std::lower_bound( sorted_vec.begin(), sorted_vec.end(), std::make_pair( in, int64_t(0) ) );
    if ( it->first == in )
        res += it->second;
    else
        res -= 200;

    return res;
}

int64_t score_it_gperf( std::string_view in )
{
    int64_t res = 0;
    switch( weekday( in ) )
    {
    case weekday( "Accept-Charset" ):              res += 9;           break;
    case weekday( "Accept-Encoding" ):             res += 98;          break;
    case weekday( "Content-Encoding" ):            res += 987;         break;
    case weekday( "Content-Length" ):              res += 9876;        break;
    case weekday( "Host" ):                        res += 98765;       break;
    case weekday( "If-Unmodified-Since" ):         res += 987654;      break;
    case weekday( "Keep-Alive" ):                  res += 987655443;   break;
    case weekday( "Referer" ):                     res += 10;          break;
    case weekday( "Upgrade-Insecure-Requests" ):   res += 11;          break;
    case weekday( "User-Agent" ):                  res += 13;          break;
    default:
        res -= 200;
    }
    return res;
}

int main()
{
    std::vector< std::string > v;
    v.push_back( "Accept" );
    v.push_back( "Accept-Charset" );
    v.push_back( "Accept-Encoding" );
    v.push_back( "Accept-Language" );
    v.push_back( "Accept-Ranges" );
    v.push_back( "Access-Control-Allow-Credentials" );
    v.push_back( "Access-Control-Allow-Headers" );
    v.push_back( "Access-Control-Allow-Methods" );
    v.push_back( "Access-Control-Allow-Origin" );
    v.push_back( "Access-Control-Expose-Headers" );
    v.push_back( "Access-Control-Max-Age" );
    v.push_back( "Access-Control-Request-Headers" );
    v.push_back( "Access-Control-Request-Method" );
    v.push_back( "Age" );
    v.push_back( "Allow" );
    v.push_back( "Authorization" );
    v.push_back( "Cache-Control" );
    v.push_back( "Clear-Site-Data" );
    v.push_back( "Connection" );
    v.push_back( "Content-Disposition" );
    v.push_back( "Content-Encoding" );
    v.push_back( "Content-Language" );
    v.push_back( "Content-Length" );
    v.push_back( "Content-Location" );
    v.push_back( "Content-Range" );
    v.push_back( "Content-Security-Policy" );
    v.push_back( "Content-Security-Policy-Report-Only" );
    v.push_back( "Content-Type" );
    v.push_back( "Cookie" );
    v.push_back( "Cookie2" );
    v.push_back( "DNT" );
    v.push_back( "Date" );
    v.push_back( "ETag" );
    v.push_back( "Expect" );
    v.push_back( "Expect-CT" );
    v.push_back( "Expires" );
    v.push_back( "Feature-Policy" );
    v.push_back( "Forwarded" );
    v.push_back( "From" );
    v.push_back( "Host" );
    v.push_back( "If-Match" );
    v.push_back( "If-Modified-Since" );
    v.push_back( "If-None-Match" );
    v.push_back( "If-Range" );
    v.push_back( "If-Unmodified-Since" );
    v.push_back( "Keep-Alive" );
    v.push_back( "Large-Allocation" );
    v.push_back( "Last-Modified" );
    v.push_back( "Location" );
    v.push_back( "Origin" );
    v.push_back( "Pragma" );
    v.push_back( "Proxy-Authenticate" );
    v.push_back( "Proxy-Authorization" );
    v.push_back( "Public-Key-Pins" );
    v.push_back( "Public-Key-Pins-Report-Only" );
    v.push_back( "Range" );
    v.push_back( "Referer" );
    v.push_back( "Referrer-Policy" );
    v.push_back( "Retry-After" );
    v.push_back( "Sec-WebSocket-Accept" );
    v.push_back( "Server" );
    v.push_back( "Server-Timing" );
    v.push_back( "Set-Cookie" );
    v.push_back( "Set-Cookie2" );
    v.push_back( "SourceMap" );
    v.push_back( "Strict-Transport-Security" );
    v.push_back( "TE" );
    v.push_back( "Timing-Allow-Origin" );
    v.push_back( "Tk" );
    v.push_back( "Trailer" );
    v.push_back( "Transfer-Encoding" );
    v.push_back( "Upgrade-Insecure-Requests" );
    v.push_back( "User-Agent" );
    v.push_back( "Vary" );
    v.push_back( "Via" );
    v.push_back( "WWW-Authenticate" );
    v.push_back( "Warning" );
    v.push_back( "X-Content-Type-Options" );
    v.push_back( "X-DNS-Prefetch-Control" );
    v.push_back( "X-Forwarded-For" );
    v.push_back( "X-Forwarded-Host" );
    v.push_back( "X-Forwarded-Proto" );
    v.push_back( "X-Frame-Options" );
    v.push_back( "X-XSS-Protection" );



    auto measure = [&]( const char *name, int64_t ( *score_it )( std::string_view ) )
    {
        constexpr int limit = 10000000;

        srand( 500 );
        timeval t0, t1;
        gettimeofday( &t0, nullptr );
        size_t res = 0;
        for ( int i = 0; i < limit; ++i )
        {
            res += score_it( v[ rand() % v.size() ] );
        }
        gettimeofday( &t1, nullptr );
        std::cout << name << ":Found score: " << res << " on " << ( ( t1.tv_sec - t0.tv_sec ) * 1000000.0 + t1.tv_usec - t0.tv_usec ) / 1000000.0 << " seconds\n";
    };

    measure( "gperf switch score ", score_it_gperf );
    measure( "unordered_map score", score_it_um );
    measure( "map score          ", score_it_map );
    measure( "sorted vector score", score_it_sorted_vector );

    return 0;
}
