set(NVWA ${CMAKE_HOME_DIRECTORY}/libs/nvwa-0.8.2/nvwa)

add_library(nvwa STATIC
    ${NVWA}/bool_array.cpp
    ${NVWA}/bool_array.h
    ${NVWA}/class_level_lock.h
    ${NVWA}/cont_ptr_utils.h
    ${NVWA}/debug_new.cpp
    ${NVWA}/debug_new.h
    ${NVWA}/fast_mutex.h
    ${NVWA}/fixed_mem_pool.h
    ${NVWA}/mem_pool_base.cpp
    ${NVWA}/mem_pool_base.h
    ${NVWA}/object_level_lock.h
    ${NVWA}/pctimer.h
    ${NVWA}/set_assign.h
    ${NVWA}/static_assert.h
    ${NVWA}/static_mem_pool.cpp
    ${NVWA}/static_mem_pool.h
)


add_library(memory STATIC
		ScopedPtr.cpp
		SharedPtr.cpp
		UniquePtr.cpp
		WeakPtr.cpp

    ${INCLUDE}/ScopedPtr.h
    ${INCLUDE}/SharedPtr.h
    ${INCLUDE}/UniquePtr.h
    ${INCLUDE}/WeakPtr.h

    ${INCLUDE}/memleak.h
    ${INCLUDE}/memleak_template_end.h
		)

target_link_libraries(memory nvwa)
