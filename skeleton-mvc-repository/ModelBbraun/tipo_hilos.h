#ifndef BBRAUN_MODEL_TIPO_HILOS
#define BBRAUN_MODEL_TIPO_HILOS

#include <ctime>
#include <string>
namespace bbraun {
	namespace model {
		namespace entities {
			class TipoHilos  {
			private:
				std::string id;
				std::tm inicioValidez;
				std::tm finalValidez;
				int tipoUSP;
				int material;
				int longitud;
				int tipoHilo;
			public:
				TipoHilos(std::string id_, std::tm inicioValidez_, std::tm finalValidez_, int tipoUSP_, int material_, int longitud_, int tipoHilo_) :
					id(id_), inicioValidez(inicioValidez_), finalValidez(finalValidez_), tipoUSP(tipoUSP_), material(material_), longitud(longitud_), tipoHilo(tipoHilo_) {};

				inline std::string getId() {
					return this->id;
				}
				inline std::tm getInicioValidez()  {
					return this->inicioValidez;
				}
				inline std::tm getFinalValidez() {
					return this->finalValidez;
				}
				inline int getTipoUSP() {
					return this->tipoUSP;
				}
				inline int getMaterial() {
					return this->material;
				}
				inline int getLongitud() {
					return this->longitud;
				}
				inline int getTipoHilo() {
					return this->tipoHilo;
				}

			};
		}
	}
}
#endif