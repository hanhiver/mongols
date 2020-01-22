#ifndef QJS_SERVER_HPP
#define QJS_SERVER_HPP

#include "http_server.hpp"
#include "file_mmap.hpp"
#include "lib/qjs/quickjs.h"
#include <string>

namespace mongols {

class qjs_server {
public:
    qjs_server() = delete;
    qjs_server(const std::string& host, int port, int timeout = 5000, size_t buffer_size = 8192, size_t thread_size = std::thread::hardware_concurrency(), size_t max_body_size = 4096, int max_event_size = 64);
    virtual ~qjs_server();
    void set_root_path(const std::string& path);
    void set_enable_session(bool);
    void set_enable_cache(bool);
    void set_enable_lru_cache(bool);
    void set_enable_bootstrap(bool);
    void set_lru_cache_expires(long long);
    void set_lru_cache_size(size_t);
    void set_session_expires(long long);
    void set_max_open_files(int);
    void set_write_buffer_size(size_t);
    void set_max_file_size(size_t);
    void set_db_path(const std::string&);
    void set_uri_rewrite(const std::pair<std::string, std::string>&);
    bool set_openssl(const std::string&, const std::string&, openssl::version_t = openssl::version_t::TLSv12, const std::string& ciphers = openssl::ciphers, long flags = openssl::flags);
    void set_enable_blacklist(bool);
    void set_enable_security_check(bool);
    void set_enable_whitelist(bool);
    void set_whitelist(const std::string&);
    void del_whitelist(const std::string&);
    void set_whitelist_file(const std::string&);
    void set_shutdown(const tcp_server::shutdown_function&);
    void run(const std::string& path);

private:
    JSRuntime* vm;
    mongols::http_server* server;
    std::string root_path;
    bool enable_bootstrap;
    file_mmap jsfile_mmap;

private:
    void work(const mongols::request& req, mongols::response& res);
    bool filter(const mongols::request& req);
};
}

#endif /* QJS_SERVER_HPP */