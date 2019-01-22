# 1sanji
Proof of Agricultural Products origin with Blockchain(EOS smart contract)

## Test
This Project use the https://github.com/cryptokylin/CryptoKylin-Testnet and It need **docker**
> Note: **You must starting docker. check above url.** 

> cd CryptoKylin-Testnet/fullnode 

> docker-compose -f docker-compose-kylin-init.yaml up -d

before do testing, have to unlock wallet.
There is 3step
1. compile
2. deploy smart contract
3. testing

### Unlock wallet
> cleos wallet unlock -n [account_name]

### Compile
> eosio-cpp -o filename.wasm filename.cpp --abigen

### Deploy
> cleos -u **https://api.kylin.alohaeos.com:443** _set contract_ [deploy_account] [Current Diractory] 

### testing 
> cleos -u **https://api.kylin.alohaeos.com:443** _push action_ [account] [function] '[param1, param2, param3 . . .]' -p [account]@active

> Note: Not only https://api.kylin.alohaeos.com:433. Is there more API nodes. find yourself.

## Check CryptoKylin transaction 
https://kylin.eosx.io/


## Reference
* easy tutorial : https://hackernoon.com/how-to-deploy-and-run-a-smart-contract-on-the-eos-blockchain-from-zero-to-hero-72ca592803ba
