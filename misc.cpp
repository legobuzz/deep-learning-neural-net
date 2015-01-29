#include "misc.h"

double Sigmoid(double z) {
	return 1.0/(1.0 + exp(-z));
}

gsl_vector* SigmoidVectorized(gsl_vector* v) {
  for (int i=0; i<v->size; i++){
  	double sigmoidEntry = Sigmoid(gsl_vector_get(v,i));
    gsl_vector_set(v, i, sigmoidEntry);
  }
  return v;
}

gsl_vector* SigmoidPrimeVectorized(gsl_vector* v) {
  for (int i=0; i<v->size; i++){
  	double sigmoidEntry = Sigmoid(gsl_vector_get(v,i));
  	double sigmoidPrimeEntry = sigmoidEntry*(1.0 - sigmoidEntry);
    gsl_vector_set(v, i, sigmoidPrimeEntry);
  }
  return v;
}

void PrintVector(const gsl_vector* v) {
  for (int i=0; i<v->size; i++){
    cout << gsl_vector_get(v, i) << endl;
  }
  cout << endl;
}

void PrintMatrix(const gsl_matrix* m) {
  for (size_t i = 0; i < m->size1; i++) {
    for (size_t j = 0; j < m->size2; j++) {
      cout << gsl_matrix_get(m, i, j) << " ";
    }
    cout << endl;
  cout << endl;
	}
}

DataSet BuildDataSet(const int setSize,const int numNeuronsInput) {
	gsl_rng* rng = GetGslRng();
	DataSet set;

	for(int i=0; i<setSize; i++) {
		set.push_back(pair<gsl_vector*, int>(RandomGaussianGslVector(rng, numNeuronsInput), i%10));
	}
	return set;
}

gsl_rng* GetGslRng() {
  gsl_rng* rng;
	int random_seed = (int)time(NULL);
	rng = gsl_rng_alloc(gsl_rng_mt19937);
	gsl_rng_set(rng, random_seed);

	return rng;
}

gsl_vector* RandomGaussianGslVector(const gsl_rng* rng, const int i) {
	gsl_vector* v = gsl_vector_alloc(i);

  for (int it = 0; it < i; it++) {
    gsl_vector_set(v, it, gsl_ran_gaussian(rng, 1.0));
  }
  return v;
}

gsl_matrix* RandomGaussianGslMatrix(const gsl_rng* rng, const int i, const int j) {
  gsl_matrix* m = gsl_matrix_alloc(i, j);

  for (int it = 0; it < i; it++) {
  	for (int jt = 0; jt < j; jt++)
  	{
      gsl_matrix_set(m, it, jt, gsl_ran_gaussian(rng, 1.0));
  	}
  }
  return m;
}

  
