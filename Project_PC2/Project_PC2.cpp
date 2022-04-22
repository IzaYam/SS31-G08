#include "Solution.h"
class Registro
{
public:
	Registro() {

	}
	Registro(float customer_ID_, float call_, float complains_, float subscripcion_, float charge_,
		float seconds_use_, float frequency_use_, float frequency_SMS_, float distinct_num_, float age_group_,
		float tariff_, float status_, float churn_, float value_) {
		this->customer_ID = customer_ID_;
		this->call = call_;
		this->complains = complains_;
		this->subscripcion = subscripcion_;
		this->charge = charge_;
		this->seconds_use = seconds_use_;
		this->frequency_use = frequency_use_;
		this->frequency_SMS = frequency_SMS_;
		this->distinct_num = distinct_num_;
		this->age_group = age_group_;
		this->tariff = tariff_;
		this->status = status_;
		this->churn = churn_;
		this->value = value_;
	}
	float getCustomerID() {
		return this->customer_ID;
	}
	float AgeGroup() {
		return this->age_group;
	}
	float GetSeconds_Use() {
		return this->seconds_use;
	}
	friend ostream& operator<< (ostream& out, const Registro& r) {
		out << r.customer_ID << " " << r.call << " " << r.complains << " " << r.subscripcion << " " << r.charge << " " << r.seconds_use << " "
			<< r.frequency_use << " " << r.frequency_SMS << " " << r.distinct_num << " " << r.age_group << " " << r.tariff << " " << r.status << " " << r.churn << endl;
		return out;
	}
	bool operator== (const Registro& r1) {
		return (this->age_group == r1.age_group && this->call == r1.call && this->charge == r1.charge && this->churn == r1.churn
			&& this->complains == r1.complains && this->distinct_num == r1.distinct_num && this->edad == r1.edad && this->frequency_SMS == r1.frequency_SMS
			&& this->frequency_use == r1.frequency_use);
	}
	~Registro() {

	}
private:
	float customer_ID;
	float call;
	float complains;
	float subscripcion;
	float charge;
	float seconds_use;
	float frequency_use;
	float frequency_SMS;
	float distinct_num;
	float age_group;
	float tariff;
	float status;
	float churn;
	float edad;
	float value;
};

class DataS
{

private:
	HashTable<Registro, int>* ht;
	string encabezado;
public:
	DataS() {
		ht = new HashTable<Registro, int>(3150);
	}
	~DataS() {

	}
	void leer(string archivo = "", bool header = true) {

		string customer_ID;
		string call;
		string complains;
		string subscripcion;
		string charge;
		string seconds_use;
		string frequency_use;
		string frequency_SMS;
		string distinct_num;
		string age_group;
		string tariff;
		string status;
		string churn;
		string value;

		float customer_ID_;
		float call_;
		float complains_;
		float subscripcion_;
		float charge_;
		float seconds_use_;
		float frequency_use_;
		float frequency_SMS_;
		float distinct_num_;
		float age_group_;
		float tariff_;
		float status_;
		float churn_;
		float value_;
		ifstream file(archivo);
		if (header)
			getline(file, encabezado);

		while (file >> customer_ID >> call >> complains >> subscripcion >> charge >> seconds_use >> frequency_use >> frequency_SMS >> distinct_num >> age_group >> tariff >> status >> churn >> value) {

			customer_ID_ = stof(customer_ID);
			call_ = stof(call);
			complains_ = stof(complains);
			subscripcion_ = stof(subscripcion);
			charge_ = stof(charge);
			seconds_use_ = stof(seconds_use);
			frequency_use_ = stof(frequency_use);
			frequency_SMS_ = stof(frequency_SMS);
			distinct_num_ = stof(distinct_num);
			age_group_ = stof(age_group);
			tariff_ = stof(tariff);
			status_ = stof(status);
			churn_ = stof(churn);
			value_ = stof(value);
			ht->insertar(customer_ID_, (Registro(customer_ID_, call_, complains_, subscripcion_, charge_, seconds_use_, frequency_use_,
				frequency_SMS_, distinct_num_, age_group_, tariff_, status_, churn_, value_)));

		}

	}
	void print() {
		cout << encabezado << endl;
		ht->print();
	}
	void Metodoforeach(int inicio, int fin) {

		cout << encabezado << endl;
		ht->For_each(inicio, fin);
	}

	void Partition(int inicio, int fin, function<bool(int)> f) {
		ht->Partition(inicio, fin, f);
	}
	void Find_if(int inicio, int fin, function<bool(int)> f) {
		cout << encabezado << endl;
		ht->Find_if(inicio, fin, f);
	}
	void Find_first_of(int Inicio, int fin) {
		ht->Find_first_of(Inicio, fin);
	}
	void Copy_if(int inicio, int fin, function<bool(int)>f) {
		cout << encabezado << endl;
		ht->copy_if(inicio, fin, f);
	}
	void adjacent_find(int Inicio, int fin) {
		ht->adjacent_find(Inicio, fin);
	}
};

int main() {
	int op;
	short aux1, aux2;


	HashTable<Registro, int>* auxiliar;
	DataS* a = new DataS();
	a->leer("dataset.txt");
	auto b = [](int i) {
		return (i % 2 == 0);
	};
	auto menor = [](int i) {
		return (i < 1000);
	};
	auto c = [](int i) {
		return (i % 2 == 1);
	};
	do
	{
		cout << "----------Menu-------------" << endl;
		cout << "1. Metodo For each" << endl;
		cout << "2. Metodo Partition" << endl;
		cout << "3. Find if" << endl;
		cout << "4. Find first of" << endl;
		cout << "5. copy if" << endl;
		cout << "6. adjacent find" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			if (aux1 < aux2)
				a->Metodoforeach(aux1, aux2);
			break;
		case 2:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			a->Partition(aux1, aux2, c);

			break;
		case 3:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			a->Find_if(aux1, aux2, c);
			break;
		case 4:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			a->Find_first_of(aux1, aux2);
			break;
		case 5:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			a->Copy_if(aux1, aux2, menor);
			break;
		case 6:
			cout << "Ingrese inicio: " << endl;
			cin >> aux1;
			cout << "Ingrese final: " << endl;
			cin >> aux2;
			a->adjacent_find(aux1, aux2);
			break;

		default:
			break;
		}
	} while (op);

}
