# prophet

The API services supported by this server are defined in libs/services.proto.

The service is able to persist state, making it resilient to server crashes. On each mutation, data is written to log files located in 'data_dir/'.

## Prerequisites - 

1. Install bazel

```
$ sudo apt-get install bazel
```

2. Install grpcurl

```
$ curl -sSL "https://github.com/fullstorydev/grpcurl/releases/download/v1.8.7/grpcurl_1.8.7_linux_x86_64.tar.gz" | sudo tar -xz -C /usr/local/bin
```

## Launch the server - 

1. Build - Initial build can take upto 20 minutes.

```
$ bazel build :prophet_server --cxxopt=-std=c++2a
```

2. Run
```
$ bazel-bin/prophet_server
```

## Sending requests to server - 

After launching the server, open another terminal to send some requests to it.

1. Send a request to process events
```
grpcurl \
-plaintext \
-proto libs/services.proto \
-d '{"events":{"ip_address":"1.2.3.4","user":"Alice"}}' \
localhost:50051 \
prophet.ProphetService/ProcessEvents
```

2. Sending a request to block an iprange
```
grpcurl \
-plaintext \
-proto libs/services.proto \
-d '{"ip_range":"100.200.0.0/16"}' \
localhost:50051 \
prophet.ProphetService/BlockIpRange
```

3. Sending a request to unblock an iprange
```
grpcurl \
-plaintext \
-proto libs/services.proto \
-d '{"ip_range":"100.200.0.0/16"}' \
localhost:50051 \
prophet.ProphetService/UnblockIpRange
```

4. Sending a request to get the list of suspicious events.
```
grpcurl \
-plaintext \
-proto libs/services.proto \
-d '{"number_of_events":"10"}' \
localhost:50051 \
prophet.ProphetService/GetSuspiciousEvents
```