#ifndef BBRAUN_MODEL_QUERY
#define BBRAUN_MODEL_QUERY
#include <string>
#include <unordered_map>
#include "utils.h"

namespace bbraun {
	namespace model {
		class Value  {
			virtual std::string getValue();
		};

		class IntegerValue : public Value {
		private:
			int value;
		public:
			IntegerValue(int value_) : value(value_) {};
			std::string getValue() {
				return bbraun::to_string<int>(value);
			}
		};

		class StringValue : public Value {
		private:
			std::string value;
		public:
			StringValue(std::string value_) : value(value_) {};
			std::string getValue() {
				return "\"" + value + "\"";
			}
		};


		class QuerySpecification {
		private:
			std::unordered_map<std::string, Value> values;
		public:
			inline void addParam(std::string key, Value value) {
				values[key] = value;
			};
		};
	}
}
#endif