#ifndef BBRAUN_MODEL_REPOSITORY
#define BBRAUN_MODEL_REPOSITORY
#include "soci/soci.h"
#include "repository_factory.h"
#include "utils.h"
#include "query.h"
#include <unordered_map>


namespace bbraun
{
	namespace model {
		template <class C> class Repository{
		public:
			//virtual public Repository(RepositoryFactory & factory) = 0;
			virtual ~Repository();
			virtual void save(C instance) = 0;
			virtual void updateById(long id) = 0;
			virtual void deleteById(long id) = 0;
			virtual std::vector<C> getAll() = 0;
			virtual std::vector<C> query(QuerySpecification & query);
		};




	}
}
#endif