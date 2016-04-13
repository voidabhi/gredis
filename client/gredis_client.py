

from grpc.beta import implementations
import imp
gredis_pb2 = imp.load_source('gredis_pb2', '../build/generated/gredis_pb2.py')

HOST = 'localhost'
PORT = 3000
TIMEOUT_SECONDS = 3


def set_value(stub, key, value):
    request = gredis_pb2.SetValueRequest(key=key, value=value)
    response = stub.SetValue(request, TIMEOUT_SECONDS)
    return response.value

def get_value(stub, key):
    request = gredis_pb2.GetValueRequest(key=key)
    response = stub.GetValue(request, TIMEOUT_SECONDS)
    return response.value

def main():
  channel = implementations.insecure_channel(HOST, PORT)
  stub = gredis_pb2.beta_create_Gredis_stub(channel)

  # some sample data for testing
  print 'Running sample data...'
  set_value(stub, 'foo', 'bar')
  set_value(stub, 'bar', 'foo')
  print get_value(stub, 'foo')


if __name__ == '__main__':
  main()
