include_directories(${CMAKE_CURRENT_BINARY_DIR})

# generate protobuf files
set(PROTO_PATH "${CMAKE_SOURCE_DIR}/protos")
set(GREDIS_PROTO "${PROTO_PATH}/gredis.proto")
set(GENERATED_PROTOBUF_PATH "${CMAKE_BINARY_DIR}/generated")
file(MAKE_DIRECTORY ${GENERATED_PROTOBUF_PATH})

set(GREDIS_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/gredis.pb.cc")
set(GREDIS_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/gredis.pb.h")
set(GREDIS_GRPC_PB_CPP_FILE "${GENERATED_PROTOBUF_PATH}/gredis.grpc.pb.cc")
set(GREDIS_GRPC_PB_H_FILE "${GENERATED_PROTOBUF_PATH}/gredis.grpc.pb.h")
set(GREDIS_GRPC_PB_PY_FILE "${GENERATED_PROTOBUF_PATH}/gredis_pb2.py")

add_custom_command(
    OUTPUT "${GREDIS_PB_H_FILE}"
           "${GREDIS_PB_CPP_FILE}"
           "${GREDIS_GRPC_PB_H_FILE}"
           "${GREDIS_GRPC_PB_CPP_FILE}"
           "${GREDIS_GRPC_PB_PY_FILE}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--cpp_out=${GENERATED_PROTOBUF_PATH}"
         "${GREDIS_PROTO}"
    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS "--proto_path=${PROTO_PATH}"
         "--grpc_out=${GENERATED_PROTOBUF_PATH}"
         "--plugin=protoc-gen-grpc=/usr/local/bin/GRPC_CPP_PLUGIN"
         "${GREDIS_PROTO}"
   COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
   ARGS "--proto_path=${PROTO_PATH}"
        "--python_out=${GENERATED_PROTOBUF_PATH}"
        "--grpc_out=${GENERATED_PROTOBUF_PATH}"
        "--plugin=protoc-gen-grpc=/usr/local/bin/GRPC_PYTHON_PLUGIN"
        "${GREDIS_PROTO}"
)

set(GENERATED_PROTOBUF_FILES
    ${GREDIS_PB_H_FILE}
    ${GREDIS_PB_CPP_FILE}
    ${GREDIS_GRPC_PB_H_FILE}
    ${GREDIS_GRPC_PB_CPP_FILE}
    ${GREDIS_GRPC_PB_PY_FILE}
)

include_directories(${GENERATED_PROTOBUF_PATH})
link_libraries(grpc++_unsecure grpc gpr ${PROTOBUF_LIBRARY})

# build source with generated protobuf files
set(GREDIS_SOURCES
 ${GENERATED_PROTOBUF_FILES}
	main.cc
)

add_executable(gredis ${GREDIS_SOURCES})
target_link_libraries(gredis ${GREDIS_LIB_DEPS})
