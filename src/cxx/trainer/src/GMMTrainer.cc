#include "trainer/GMMTrainer.h"

using namespace Torch::machine;

Torch::trainer::GMMTrainer::GMMTrainer(bool update_means, bool update_variances, bool update_weights) :
  EMTrainer<GMMMachine, Torch::database::Arrayset>(), update_means(update_means), update_variances(update_variances), update_weights(update_weights) {
}

Torch::trainer::GMMTrainer::~GMMTrainer() {
  
}

void Torch::trainer::GMMTrainer::initialization(Torch::machine::GMMMachine& gmm, const Torch::database::Arrayset& data) {
  // Allocate memory for the sufficient statistics and initialise
  m_ss.resize(gmm.getNGaussians(),gmm.getNInputs());
}

double Torch::trainer::GMMTrainer::eStep(Torch::machine::GMMMachine& gmm, const Torch::database::Arrayset& data) {
  m_ss.init();
  // Calculate the sufficient statistics and save in m_ss
  gmm.accStatistics(data, m_ss);
  return m_ss.log_likelihood / m_ss.T;
}
