#ifndef BBRAUN_MODEL_REPOSITORY_FACTORY
#define BBRAUN_MODEL_REPOSITORY_FACTORY
#include "soci/soci.h"

namespace bbraun
{

	namespace model {
		class RepositoryFactory{
		public:
			 virtual std::shared_ptr<soci::session> makeSession() = 0;
		};
	}
}

#endif