

namespace bbraun {
	namespace model {
		ODBCRepository::ODBCRepository(std::shared_ptr<soci::session> & currentSession_) : currentSession(currentSession_) {};

		ODBCRepository::ODBCRepository(RepositoryFactory & factory) {
			currentSession = factory.makeSession();
		}
		ODBCRepository::ODBCRepository(ODBCRepository&& other)  {
			ODBCRepository newRepository(other.currentSession);
		}
		ODBCRepository& ODBCRepository::operator= (ODBCRepository&& other)
		{
			std::swap(currentSession,other.currentSession);
			return *this;
		}
		ODBCRepository& ODBCRepository::operator= (const ODBCRepository& other)
		{
			ODBCRepository tmp(other);
			*this = std::move(tmp);
			return *this;
		}

		ODBCRepository::~ODBCRepository() {
			(*currentSession.get()).close();
		}


		/* functions to implement */
		void ODBCRepository::save (bbraun::model::entities::TipoHilos instance) {
			//(*currentSession.get()) << "insert ";
		};

		void ODBCRepository::updateById(long id) {

		};

		void ODBCRepository::deleteById(long id) {

		};

		std::vector<bbraun::model::entities::TipoHilos> getAll() {
			std::vector<bbraun::model::entities::TipoHilos> values;
			return values;
		};

		std::vector<bbraun::model::entities::TipoHilos> query(QuerySpecification & query) {
			std::vector<bbraun::model::entities::TipoHilos> values;
			return values;
		};

	}
}
