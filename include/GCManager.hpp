#include "gc.h"
#include "mimalloc.h"
#include <cstdio>





/* Decided to build a smart Memeory Manager System for geode mods to 
 * implement but this could be useful for other programs outside of 
 * geometry dash, this was primary a concept after I had a chat with 
 * IAndy about it , I will wrap it with a gc library I found recently to 
 * help with this */


/* todo maybe add in a mutex? */

class GCManager {
private:
    GarbageCollector* m_gc;
public:
    GCManager();

    /* Returns a lower level Pointer of the garbage collector */
    GarbageCollector* c_ptr(){
        return m_gc;
    }

    void* malloc(size_t size){
        return gc_malloc(m_gc, size);
    }

    void* calloc(size_t count, size_t size){
        return gc_calloc(m_gc, count, size); 
    }

    void* realloc(void* heap, size_t newsize){
        return gc_realloc(m_gc, heap, newsize);
    }

    void free(void* heap){
        if (heap != nullptr) {
            return gc_free(m_gc, heap);
        }
    }

    void stop(){
        gc_stop(m_gc);
    }
    
    void resume(){
        gc_resume(m_gc);
    }

    void pause(){
        gc_pause(m_gc);
    }

    #if ((__cplusplus >= 201103L) || (_MSC_VER > 1900)) 
    template <class T, class ...Args>
    T* construct(T* cls, Args&&...args){
        T* c = reinterpret_cast<T*>(gc_malloc(m_gc, sizeof(cls)));
        if (c == nullptr) return c;
        c = T(std::forward<Args>(args)...);
        return c;
    }
    #endif

    template <class T>
    void destroy(T* cls) mi_attr_noexcept {
        cls->~T();
        free(cls);
    }

    ~GCManager();

    static GCManager* sharedState();
    static void releaseState();
};

/* To be a little more Robtop-like I have added a GCM Macro to do just that... */
#define GCM GCManager::sharedState()
#define GCMFinish GCManager::releaseState()
#define GCMNew(Class, ...) GCM->construct(Class, __VA_ARGS__)
#define GCMDelete(Class) GCM->destroy(Class)

#define GCMVERSION "0.0.1-beta"
