#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <fstream>
#include <stdexcept>

class VectorizedEnv {
    public:
    VectorizedEnv(int num_envs, int observation_size, int action_size,
        bool normalize_obs = true, bool normalize_reward = true)
        : num_envs_(num_envs), observation_size_(observation_size), action_size_(action_size),
        normalize_obs_(normalize_obs), normalize_reward_(normalize_reward),
        training_(true) {
        obs_mean_.resize(observation_size, 0);
        obs_std_.resize(observation_size, 1);
        reward_mean_ = 0;
        reward_std_ = 1;
    }

    void SetTraining(bool training) {
        training_ = training;
    }

    int GetNumEnvs() const {
        return num_envs_;
    }

    int GetObservationSize() const {
        return observation_size_;
    }

    int GetActionSize() const {
        return action_size_;
    }

    std::vector<std::vector<double>> Reset() {
        std::vector<std::vector<double>> observations(num_envs_);
        for (int i = 0; i < num_envs_; ++i) {
            observations[i] = ResetEnv(i);
            if (normalize_obs_) {
                observations[i] = NormalizeObs(observations[i]);
            }
        }
        return observations;
    }

    std::vector<std::tuple<std::vector<double>, double, bool>> Step(const std::vector<int>& actions) {
        if (actions.size() != num_envs_) {
            throw std::invalid_argument("Invalid action size");
        }

        std::vector<std::tuple<std::vector<double>, double, bool>> results(num_envs_);
        for (int i = 0; i < num_envs_; ++i) {
            std::vector<double> next_obs;
            double reward;
            bool done;
            std::tie(next_obs, reward, done) = StepEnv(i, actions[i]);

            if (normalize_obs_) {
                next_obs = NormalizeObs(next_obs);
            }
            if (normalize_reward_ && training_) {
                reward = NormalizeReward(reward);
            }

            results[i] = std::make_tuple(next_obs, reward, done);
        }
        return results;
    }

    void Render() {
        // Implement render logic for all environments
    }

    std::vector<std::vector<double>> GetObs() {
        std::vector<std::vector<double>> observations(num_envs_);
        for (int i = 0; i < num_envs_; ++i) {
            observations[i] = GetObsEnv(i);
            if (normalize_obs_) {
                observations[i] = NormalizeObs(observations[i]);
            }
        }
        return observations;
    }

    void Save(const std::string& filename) {
        std::ofstream ofs(filename);
        if (!ofs) {
            throw std::runtime_error("Could not open file for saving");
        }

        for (double value : obs_mean_) {
            ofs << value << " ";
        }
        ofs << std::endl;

        for (double value : obs_std_) {
            ofs << value << " ";
        }
        ofs << std::endl;

        ofs << reward_mean_ << " " << reward_std_ << std::endl;
    }

    void Load(const std::string& filename) {
        std::ifstream ifs(filename);
        if (!ifs) {
            throw std::runtime_error("Could not open file for loading");
        }

        for (double& value : obs_mean_) {
            ifs >> value;
        }

        for (double& value : obs_std_) {
            ifs >> value;
        }

        ifs >> reward_mean_ >> reward_std_;
    }

    std::vector<double> NormalizeObs(const std::vector<double>& obs) {
        std::vector<double> normalized_obs(obs.size());
        for (int i = 0; i < obs.size(); ++i) {
            normalized_obs[i] = (obs[i] - obs_mean_[i]) / obs_std_[i];
        }
        return normalized_obs;
    }

    double NormalizeReward(double reward) {
        return (reward - reward_mean_) / reward_std_;
    }

    void UpdateObs(const std::vector<std::vector<double>>& batch_obs) {
        // Update the observation normalization parameters using the provided batch of observations
    }

    void UpdateReward(const std::vector<double>& batch_rewards) {
        // Update the reward normalization parameters using the provided batch of rewards
    }

    protected:
    virtual std::vector<double> ResetEnv(int env_idx) = 0;
    virtual std::tuple<std::vector<double>, double, bool> StepEnv(int env_idx, int action) = 0;
    virtual std::vector<double> GetObsEnv(int env_idx) = 0;

    private:
    int num_envs_;
    int observation_size_;
    int action_size_;
    bool normalize_obs_;
    bool normalize_reward_;
    bool training_;

    std::vector<double> obs_mean_;
    std::vector<double> obs_std_;
    double reward_mean_;
    double reward_std_;
};