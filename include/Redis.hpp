
#ifndef _GREDIS_UTILS_REDIS_HPP_
#define _GREDIS_UTILS_REDIS_HPP_

#include <hiredis/hiredis.h>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class Redis {
public:
    Redis();

    Redis(string hostname, int port);

    bool connect();

    bool set(string key, string value);

    bool setex(string key, string value, int ttl);

    string get(string key);

    bool del(string key);

    bool close();

    ~Redis();

private:
    string hostname;
    int port;
    redisContext *context;
    redisReply *reply;
    bool connected;
};


Redis::Redis() {
    this->hostname = "127.0.0.1";
    this->port = 6379;
    this->connected = false;
}

Redis::Redis(string hostname, int port) {
    this->hostname = hostname;
    this->port = port;
    this->connected = false;
}

bool Redis::connect() {
    if (!this->connected) {
        struct timeval timeout = {1, 500000};
        this->context = redisConnectWithTimeout(this->hostname.c_str(), this->port, timeout);
        if (this->context == NULL || this->context->err) {
                   if (this->context) {
                       string s("Connection error: ");
                       s = s + this->context->errstr;
                       s = s + "\n";
                       throw runtime_error(s.c_str());
                       redisFree(this->context);
                   } else {
                       string s("Connection error: can't allocate redis context object\n");
                       throw runtime_error(s.c_str());
                   }
            return false;
        }
        this->connected = true;
    }
    return this->connected;
}

bool Redis::set(string key, string value) {
    if (!this->connected) {
        throw runtime_error("Must be connected to call 'set'");
    }
    reply = (redisReply *) redisCommand(this->context, "SET %b %b", key.c_str(), (size_t) key.size(),
                                        value.c_str(), (size_t) value.size());
    if (reply->type == REDIS_REPLY_ERROR) {
        string s("'set' command failed: ");
        s = s + reply->str;
        freeReplyObject(reply);
        throw runtime_error(s.c_str());
    }
    freeReplyObject(reply);
    return true;
}

bool Redis::setex(string key, string value, int ttl) {
    if (!this->connected) {
        throw runtime_error("Must be connected to call 'setex'");
    }
    reply = (redisReply *) redisCommand(this->context, "SET %b %b EX %b", key.c_str(), (size_t) key.size(),
                                        value.c_str(), (size_t) value.size(), to_string(ttl).c_str(), (size_t)to_string(ttl).size());
    if (reply->type == REDIS_REPLY_ERROR) {
        string s("'set' command failed: ");
        s = s + reply->str;
        freeReplyObject(reply);
        throw runtime_error(s.c_str());
    }
    freeReplyObject(reply);
    return true;
}

bool Redis::del(string key) {
    if (!this->connected) {
        throw runtime_error("Must be connected to call 'del'");
    }
    reply = (redisReply *) redisCommand(this->context, "DEL %b", key.c_str(), (size_t) key.size());
    if (reply->type == REDIS_REPLY_ERROR) {
        string s("'del' command failed: ");
        s = s + reply->str;
        freeReplyObject(reply);
        throw runtime_error(s.c_str());
    }
    freeReplyObject(reply);
    return true;
}

string Redis::get(string key) {
    if (!this->connected) {
        throw runtime_error("Must be connected to call 'get'");
    }
    reply = (redisReply *) redisCommand(this->context, "GET %b", key.c_str(), (size_t) key.size());
    if (reply->type == REDIS_REPLY_ERROR) {
        string s("'get' command failed: ");
        s = s + reply->str;
        freeReplyObject(reply);
        throw runtime_error(s.c_str());
    }
    if (reply->type == REDIS_REPLY_STRING) {
        string s(reply->str, reply->len);
        freeReplyObject(reply);
        return s;
    }
    freeReplyObject(reply);
    return NULL;

}

bool Redis::close() {
    if (this->connected && this->context) {
        try {
            redisFree(this->context);
        } catch(...) {
            return true;
        }
        return true;
    } else {
        return false;
    }
}

Redis::~Redis() {
    close();
}

#endif /* _SZAUTH_UTILS_REDIS_HPP_ */
