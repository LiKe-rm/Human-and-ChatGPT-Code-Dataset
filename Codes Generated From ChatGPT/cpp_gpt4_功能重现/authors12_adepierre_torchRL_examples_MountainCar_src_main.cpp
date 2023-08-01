#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <random>
#include <ctime>
#include "PPO.h"
#include "MountainCarContinuousEnv.h"
#include "VectorizedEnv.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <train|generate>" << endl;
        return 1;
    }

    string mode(argv[1]);
    const int num_envs = 8;

    if (mode == "train") {
        auto env = make_shared<MountainCarContinuousEnv>();
        auto vectorized_env = make_shared<VectorizedEnv>(env, num_envs);

        PPOArgs ppo_args;
        ppo_args.num_episodes = 1000;
        ppo_args.batch_size = 2048;
        ppo_args.k_epochs = 10;
        ppo_args.eps_clip = 0.2;
        ppo_args.gamma = 0.99;
        ppo_args.lr = 0.0003;
        ppo_args.policy_path = "trained_policy.pth";

        PPO ppo(vectorized_env, ppo_args);
        ppo.learn();

    } else if (mode == "generate") {
        auto env = make_shared<MountainCarContinuousEnv>();

        for (int i = 0; i < 10; ++i) {
            string exp_path = "experiment_" + to_string(i);
            unsigned seed = static_cast<unsigned>(time(nullptr) + i);
            env->seed(seed);

            PPOArgs ppo_args;
            ppo_args.policy_path = exp_path + "/trained_policy.pth";

            PPO ppo(env, ppo_args);
            vector<double> rewards = ppo.play(100);

            string csv_file = exp_path + "/played.csv";
            ofstream output(csv_file);
            if (!output.is_open()) {
                cerr << "Cannot open " << csv_file << " for writing." << endl;
                continue;
            }
            for (const auto& reward : rewards) {
                output << reward << endl;
            }
            output.close();
        }

    } else {
        cerr << "Invalid mode. Use 'train' or 'generate'." << endl;
        return 1;
    }

    return 0;
}
