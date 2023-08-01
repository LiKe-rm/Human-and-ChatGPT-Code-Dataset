#include <iostream>
#include <vector>
#include <assert.h>
#include <bitcoin/wallet/wallet.h>
#include <bitcoin/chain/chain.h>

using namespace bc;
using namespace wallet;
using namespace chain;

// CoinSelection test function
void CoinSelectionTest()
{
    // Create a wallet
    wallet::hd_wallet wallet("my_password");

    // Add 1000 coins with value 1000 BTC and 1 coin with value 3 BTC
    for (int i = 0; i < 1000; i++) {
        wallet.receive(coin(100000000));
    }
    wallet.receive(coin(300000));

    // Select coins using the SelectCoinsMinConf algorithm
    std::vector<output_point> selected_coins;
    uint64_t target_value = 100300000; // 1003 BTC
    uint64_t fee = 0;
    uint32_t min_conf = 1;
    SelectCoinsMinConf(selected_coins, fee, wallet, target_value, min_conf);

    // Check that the algorithm selected two coins with total value of 1003 BTC
    assert(selected_coins.size() == 2);
    assert(selected_coins[0].value() + selected_coins[1].value() == target_value);
}

// BnBExhaustion test function
void BnBExhaustionTest()
{
    // Create a wallet
    wallet::hd_wallet wallet("my_password");

    // Generate a difficult coin selection scenario
    std::vector<coin> coins;
    for (int i = 0; i < 1000; i++) {
        coins.push_back(coin(100000000));
    }
    coins.push_back(coin(300000));

    // Repeat the test 650 times
    for (int i = 0; i < 650; i++) {
        // Select coins using the SelectCoinsBnB algorithm
        std::vector<output_point> selected_coins;
        uint64_t target_value = 100300000; // 1003 BTC
        uint64_t fee = 0;
        SelectCoinsBnB(selected_coins, fee, coins, target_value);

        // Check that the algorithm selected coins with total value of at least 1003 BTC
        uint64_t total_value = 0;
        for (auto coin : selected_coins) {
            total_value += coin.value();
        }
        assert(total_value >= target_value);
    }
}

int main()
{
    CoinSelectionTest();
    BnBExhaustionTest();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
