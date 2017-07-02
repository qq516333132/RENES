
#include <stdio.h>
#include <functional>

#pragma once

namespace ReNes {
    
    static char g_buffer[1024];
    
    static std::function<void(const char*)> g_callback;
    static bool g_logEnabled = false;
    
    bool log(const char* format, ...)
    {
        if (!g_logEnabled)
            return true;
        
        va_list args;
        va_start(args, format);
        vsprintf(g_buffer, format, args);
        va_end(args);
        
        if (g_callback != 0)
        {
            g_callback(g_buffer);
        }
        else
        {
            printf("%s", g_buffer);
        }
        
        return true;
    }
    
    
    void setLogCallback(std::function<void(const char*)> callback)
    {
        g_callback = callback;
    }
    
    void setLogEnabled(bool enabled)
    {
        g_logEnabled = enabled;
    }
    
    struct bit8 {
        
        void set(uint8_t offset, int value)
        {
            assert(value == 0 || value == 1);
            
            _data &= ~(0x1 << offset); // set 0
            _data |= ((value % 2) << offset);
        }
        
        uint8_t get(uint8_t offset) const
        {
            return (_data >> offset) & 0x1;
        }
        
    private:
        uint8_t _data; // 8bit
    };
    
    
    template <typename T>
    inline T const& __max (T const& a, T const& b)
    {
        // if a < b then use b else use a
        return  a < b ? b : a;
    }
    
    template <typename T>
    inline T const& __min (T const& a, T const& b)
    {
        // if a < b then use b else use a
        return  a > b ? b : a;
    }
    
#ifndef NES_MAX
#define NES_MAX(a, b) __max(a, b)
#endif
    
#ifndef NES_MIN
#define NES_MIN(a, b) __min(a, b)
#endif
}
