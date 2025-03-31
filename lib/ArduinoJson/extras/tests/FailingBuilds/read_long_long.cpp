// ArduinoJson - https://arduinojson.org
// Copyright © 2014-2025, Benoit BLANCHON
// MIT License

#define ARDUINOJSON_USE_LONG_LONG 0
#include <ArduinoJson.h>

#if defined(__SIZEOF_LONG__) && __SIZEOF_LONG__ >= 8
#  error This test requires sizeof(long) < 8
#endif

ARDUINOJSON_ASSERT_INTEGER_TYPE_IS_SUPPORTED(long long)
int main() {
  JsonDocument doc;
  doc["dummy"].as<long long>();
}
