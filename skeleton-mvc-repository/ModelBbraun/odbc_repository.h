#ifndef BBRAUN_ODBC_REPOSITORY
#define BBRAUN_ODBC_REPOSITORY

#include "repository.h"
#include "tipo_hilos.h"
#include "repository_factory.h"
#include "query.h"
namespace bbraun {
	namespace model {
		class ODBCRepository : public bbraun::model::Repository < bbraun::model::entities::TipoHilos > {
			private:
				std::shared_ptr<soci::session> currentSession;
				
			public:
				ODBCRepository(std::shared_ptr<soci::session> & currentSession);
				ODBCRepository(RepositoryFactory & factory);
				/* Apply three rule*/
				ODBCRepository(ODBCRepository&& other);
				ODBCRepository& operator= (ODBCRepository&& other);
				ODBCRepository& operator= (const ODBCRepository& other);
				~ODBCRepository();

				void save(bbraun::model::entities::TipoHilos instance);
				void updateById(long id);
				void deleteById(long id);
				std::vector<bbraun::model::entities::TipoHilos> getAll();
				std::vector<bbraun::model::entities::TipoHilos> query(QuerySpecification & query);
		};

		class ODBCFactory : public RepositoryFactory {
		private:
			std::string configurationFile;
		public:
			ODBCFactory(std::string configurationFile_);
		};

	}
}
#endif