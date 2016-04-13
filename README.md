
## Gredis

Redis server built over grpc

### Required Libraries

- grpc
- Hiredis
- Protobuf

### Building

```
  mkdir build
  cd build
  cmake ..
  make
```

### Running

**Server**

```bash
   # redis server should be running
  ./gredis_server
```

**Client**

```bash
  cd client
  virtualenv venv
  source venv/bin/activate
  pip install -r requirements.txt
  python gredis_client.py
```

### Contributing

- Please use the [issue tracker](https://github.com/voidabhi/gredis/issues) to report any bugs or file feature requests.


### License

```
Copyright 2016 Abhijeet Mohan - https://github.com/voidabhi/gredis

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
```
