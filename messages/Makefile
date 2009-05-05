all: worker discovery

worker: worker.proto
	protoc --cpp_out=src worker.proto

discovery: discovery.proto
	protoc --cpp_out=src discovery.proto
