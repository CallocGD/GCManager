#include "../include/GCManager.hpp"
#include "../mimalloc/include/mimalloc.h"

static GCManager* GLOBAL_GCMANAGER;

GCManager::GCManager(){
    m_gc = reinterpret_cast<GarbageCollector*>(mi_malloc(sizeof(GarbageCollector)));
    gc_start(m_gc, nullptr);
}

GCManager* GCManager::sharedState(){
    mi_stl_allocator<GCManager>GCM_alloc;
    if (GLOBAL_GCMANAGER == nullptr){
       GCM_alloc.construct(GLOBAL_GCMANAGER);
    }
    return GLOBAL_GCMANAGER;
}

GCManager::~GCManager(){
    stop();
    mi_free(m_gc);
}

void GCManager::releaseState(){
    mi_stl_allocator<GCManager>GCM_alloc;
    GCM_alloc.destroy(GCManager::sharedState());
}

