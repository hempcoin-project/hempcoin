// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers
// Copyright (c) 2017 The Hempcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "libzerocoin/Params.h"
#include "chainparams.h"
#include "random.h"
#include "util.h"
#include "utilstrencodings.h"

#include <assert.h>

#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

/**
 * Main network
 */
static bool regenerate = false;

//! Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress>& vSeedsOut, const SeedSpec6* data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

//   What makes a good checkpoint block?
// + Is surrounded by blocks with reasonable timestamps
//   (no blocks before with a timestamp after, none after with
//    timestamp before)
// + Contains no strange transactions
static Checkpoints::MapCheckpoints mapCheckpoints =
    boost::assign::map_list_of
(0, uint256("0x000006594dc0c6f2c09737bd0d87e10ad81c6ae199089208cc0f9f91e625ce8a"))
(1086, uint256("0xb7b135163eefe88fd377349e52e8c65a88cb73a298dd00eddb34fe7ec5d86d57"))
(2955, uint256("0xafd52c15e6a1b2d3a843c258982a736441aafb521556d3471eeaf0bcc914061a"))
(20012, uint256("0x5becb378600bbe8dc45e2f70a02b75ac12d58ac47fea0e62c3e773189148ddad"))
(329843, uint256("0x32aca030d22c56a7c4a7e8451000b0e9f64bfdd5ceca8129b7ac192c6785e3eb"));

static const Checkpoints::CCheckpointData data = {
    &mapCheckpoints,
    1549463071, // * UNIX timestamp of last checkpoint block
    682785,    // * total number of transactions between genesis and last checkpoint
                //   (the tx=... number in the SetBestChain debug.log lines)
    1500        // * estimated number of transactions per day after checkpoint
};

static Checkpoints::MapCheckpoints mapCheckpointsTestnet =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataTestnet = {
    &mapCheckpointsTestnet,
    1740710,
    0,
    250};

static Checkpoints::MapCheckpoints mapCheckpointsRegtest =
    boost::assign::map_list_of(0, uint256("0x001"));
static const Checkpoints::CCheckpointData dataRegtest = {
    &mapCheckpointsRegtest,
    1454124731,
    0,
    100};

libzerocoin::ZerocoinParams* CChainParams::Zerocoin_Params() const
{
    assert(this);
    static CBigNum bnTrustedModulus(zerocoinModulus);
    static libzerocoin::ZerocoinParams ZCParams = libzerocoin::ZerocoinParams(bnTrustedModulus);

    return &ZCParams;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        networkID = CBaseChainParams::MAIN;
        strNetworkID = "main";
        /**
         * The message start string is designed to be unlikely to occur in normal data.
         * The characters are rarely used upper ASCII, not valid as UTF-8, and produce
         * a large 4-byte int at any alignment.
         */
        pchMessageStart[0] = 0x73;
        pchMessageStart[1] = 0xA1;
        pchMessageStart[2] = 0x06;
        pchMessageStart[3] = 0xca;
        vAlertPubKey = ParseHex("04e4d80fcaf529731b77ed2287664326f1686a69d8542fa043af1650df819355c0e86d71cbbdfaa7b5a31101b799419a114f8664926893174d93b07822e86200e6");
        nDefaultPort = 27577;
        bnProofOfWorkLimit = ~uint256(0) >> 20; // Hempcoin starting difficulty is 1 / 2^12
        nSubsidyHalvingInterval = 210000;
        nMaxReorganizationDepth = 100;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Hempcoin: 1 day
        nTargetSpacing = 1 * 60;  // Hempcoin: 1 minute
        nMaturity = 10;
        nMasternodeCountDrift = 20;
        nMaxMoneyOut = 280000000 * COIN;

        /** Height or Time Based Activations **/
        nLastPOWBlock = 200;
        nModifierUpdateBlock = 999999999;
        nZerocoinStartHeight = 201;
        nAccumulatorStartHeight = 1;
        nZerocoinStartTime = 1528921408; // 
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = ~1; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = ~1; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = ~1; //Last valid accumulator checkpoint
        
        /**
         * Build the genesis block. Note that the output of the genesis coinbase cannot
         * be spent as it did not originally exist in the database.
         * Mobay 2018
         * CBlock(hash=00000ffd590b14, ver=1, hashPrevBlock=00000000000000, hashMerkleRoot=e0028e, nTime=1390095618, nBits=1e0ffff0, nNonce=28917698, vtx=1)
         *   CTransaction(hash=e0028e, ver=1, vin.size=1, vout.size=1, nLockTime=0)
         *     CTxIn(COutPoint(000000, -1), coinbase 04ffff001d01044c5957697265642030392f4a616e2f3230313420546865204772616e64204578706572696d656e7420476f6573204c6976653a204f76657273746f636b2e636f6d204973204e6f7720416363657074696e6720426974636f696e73)
         *     CTxOut(nValue=50.00000000, scriptPubKey=0xA9037BAC7050C479B121CF)
         *   vMerkleTree: e0028e
         */
        const char* pszTimestamp = "The Denver Post - Colorado's marijuana industry would get bank access, federal OK ...";
        CMutableTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 0 * COIN;
        txNew.vout[0].scriptPubKey = CScript() << ParseHex("04c0104e4e786dd926ac367f4a48de6ebdbd68e54d8497899865d4c5c7a49f0e170413d535af209363dd0df618e3b24634c2b92e6cee762b849d484a6746370b10") << OP_CHECKSIG;
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1528499522;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 20650291;

		hashGenesisBlock = genesis.GetHash();
        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Mainnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";
            }
        } else {
            LogPrintf("Mainnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x000006594dc0c6f2c09737bd0d87e10ad81c6ae199089208cc0f9f91e625ce8a"));
            assert(genesis.hashMerkleRoot == uint256("0xf81d41745e6e49672fdec6c32ef361b71e5ca817f3d565a037d8398e4a96a33f"));
        }

        //  Mainnet DNS Seeders
	    vSeeds.push_back(CDNSSeedData("dns1-a.hempcoin.org", "dns1-a.hempcoin.org"));         // Primary DNS Seeder
	    vSeeds.push_back(CDNSSeedData("dns2-a.hempcoin.org", "dns2-a.hempcoin.org"));         // Secondary DNS Seeder

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 66);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 38);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 212);
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x02)(0x2D)(0x25)(0x33).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x02)(0x21)(0x31)(0x2B).convert_to_container<std::vector<unsigned char> >();
        // 	BIP44 coin type is from https://github.com/satoshilabs/slips/blob/master/slip-0044.md
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0xbc).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = false;
        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;
        fSkipProofOfWorkCheck = false;
        fTestnetToBeDeprecatedFieldRPC = false;
        fHeadersFirstSyncingActive = false;

        nPoolMaxTransactions = 3;
        strSporkKey = "04c43924c16a8e62bbf03be70654c17da536e9b065b5f5388a1bb8380ebbf2139792c3189a7ffcb801c1cdb28e7446083ccad7a9ce84bb213e3f332a5ba5647c43";
        strObfuscationPoolDummyAddress = "TpwGAZBXNUQeryN9RxFu75Dc4Xiv4enXBQ";
        nStartMasternodePayments = 1528921408; //Wednesday, 13 June 2018 21:23:24 GMT+01:00 DST

        /** Zerocoin */
        zerocoinModulus = "0xc95577b6dce0049b0a20c779af38079355abadde1a1d80c353f6cb697a7ae5a087bad39caa5798478551d0f9d91e6267716506f32412de1d19d17588765eb9502b85c6a18abdb05791cfd8b734e960281193705eeece210920cc922b3af3ceb178bf12c22eb565d5767fbf19545639be8953c2c38ffad41f3371e4aac750ac2d7bd614b3faabb453081d5d88fdbb803657a980bc93707e4b14233a2358c97763bf28f7c933206071477e8b371f229bc9ce7d6ef0ed7163aa5dfe13bc15f7816348b328fa2c1e69d5c88f7b94cee7829d56d1842d77d7bb8692e9fc7b7db059836500de8d57eb43c345feb58671503b932829112941367996b03871300f25efb5";
        nMaxZerocoinSpendsPerTransaction = 7; // Assume about 20kb each
        nMinZerocoinMintFee = 1 * ZCENT; //high fee required for zerocoin mints
        nMintRequiredConfirmations = 20; //the maximum amount of confirmations until accumulated in 19
        nRequiredAccumulation = 1;
        nDefaultSecurityLevel = 100; //full security level for accumulators
        nZerocoinHeaderVersion = 4; //Block headers must be this version once zerocoin is active
        nBudget_Fee_Confirmations = 6; // Number of confirmations for the finalization fee
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return data;
    }
};
static CMainParams mainParams;

/**
 * Testnet (v3)
 */
class CTestNetParams : public CMainParams
{
public:
    CTestNetParams()
    {
        networkID = CBaseChainParams::TESTNET;
        strNetworkID = "test";
        pchMessageStart[0] = 0x22;
        pchMessageStart[1] = 0x62;
        pchMessageStart[2] = 0xd3;
        pchMessageStart[3] = 0x54;
        vAlertPubKey = ParseHex("041350192b43b7c956abf2b0ddf46e5ee693bba9e276e3c10b0a737eebd8419f5be32978117ad908032e1fd0a05e6b8f795c06e4e8e86c0ddb9238b04b7f1d7584");
        nDefaultPort = 51434;
        nEnforceBlockUpgradeMajority = 51;
        nRejectBlockOutdatedMajority = 75;
        nToCheckBlockUpgradeMajority = 100;
        nMinerThreads = 0;
        nTargetTimespan = 1 * 60; // Hempcoin: 1 day
        nTargetSpacing = 1 * 60;  // Hempcoin: 1 minute
        nLastPOWBlock = 200;
        nMaturity = 15;
        nMasternodeCountDrift = 4;
        nModifierUpdateBlock = 51197; //approx Mon, 17 Apr 2017 04:00:00 GMT
        nMaxMoneyOut = 43199500 * COIN;
        nZerocoinStartHeight = 20000;
        nZerocoinStartTime = 1501776000;
        nBlockEnforceSerialRange = 1; //Enforce serial range starting this block
        nBlockRecalculateAccumulators = 9908000; //Trigger a recalculation of accumulators
        nBlockFirstFraudulent = 9891737; //First block that bad serials emerged
        nBlockLastGoodCheckpoint = 9891730; //Last valid accumulator checkpoint
        
        //! Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nTime = 1549470637;
        genesis.nNonce = 960725;

	    hashGenesisBlock = genesis.GetHash();
            if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Testnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Testnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x00000d89f37669d8e6228bc0f3e601806fb544504df4d25db9abdf53680ec3d8"));
            assert(genesis.hashMerkleRoot == uint256("0xf81d41745e6e49672fdec6c32ef361b71e5ca817f3d565a037d8398e4a96a33f"));
        }

        vFixedSeeds.clear();
        vSeeds.clear();
        vSeeds.push_back(CDNSSeedData("test.hempcoin.org", "test.hempcoin.org"));         // Single node address
        vSeeds.push_back(CDNSSeedData("testnet1.hempcoin.org", "testnet1.hempcoin.org"));       // Single node address
        vSeeds.push_back(CDNSSeedData("testnet.hempcoincoin.org", "testnet.hempcoincoin.org"));       // Single node address


        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 100); // Testnet hempcoin addresses start with 'x' or 'y'
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 15);  // Testnet hempcoin script addresses start with '8' or '9'
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);     // Testnet private keys start with '9' or 'c' (Bitcoin defaults)
        // Testnet hempcoin BIP32 pubkeys start with 'DRKV'
        base58Prefixes[EXT_PUBLIC_KEY] = boost::assign::list_of(0x3a)(0x80)(0x61)(0xa0).convert_to_container<std::vector<unsigned char> >();
        // Testnet hempcoin BIP32 prvkeys start with 'DRKP'
        base58Prefixes[EXT_SECRET_KEY] = boost::assign::list_of(0x3a)(0x80)(0x58)(0x37).convert_to_container<std::vector<unsigned char> >();
        // Testnet hempcoin BIP44 coin type is '1' (All coin's testnet default)
        base58Prefixes[EXT_COIN_TYPE] = boost::assign::list_of(0x80)(0x00)(0x00)(0x01).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        fRequireRPCPassword = true;
        fMiningRequiresPeers = true;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = false;
        fRequireStandard = false;
        fMineBlocksOnDemand = false;
        fTestnetToBeDeprecatedFieldRPC = true;

        nPoolMaxTransactions = 2;
        strSporkKey = "0469497584dbdb6bfdcf39edcbd0dce5072805d40fd70b4e8055454a2f7372cfd5d30ec852427642dbfe0ad8e65652fdea5abe5b3fce0e488eb51ae50c8d46da33";
        strObfuscationPoolDummyAddress = "xp87cG8UEQgzs1Bk67Yk884C7pnQfAeo7q";
        nStartMasternodePayments = 1420837558; //Fri, 09 Jan 2015 21:05:58 GMT
        nBudget_Fee_Confirmations = 3; // Number of confirmations for the finalization fee. We have to make this very short
                                       // here because we only have a 8 block finalization window on testnet
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataTestnet;
    }
};
static CTestNetParams testNetParams;

/**
 * Regression test
 */
class CRegTestParams : public CTestNetParams
{
public:
    CRegTestParams()
    {
        networkID = CBaseChainParams::REGTEST;
        strNetworkID = "regtest";
        strNetworkID = "regtest";
        pchMessageStart[0] = 0x1a;
        pchMessageStart[1] = 0x6f;
        pchMessageStart[2] = 0x13;
        pchMessageStart[3] = 0x35;
        nSubsidyHalvingInterval = 150;
        nEnforceBlockUpgradeMajority = 750;
        nRejectBlockOutdatedMajority = 950;
        nToCheckBlockUpgradeMajority = 1000;
        nMinerThreads = 1;
        nTargetTimespan = 24 * 60 * 60; // Hempcoin: 1 day
        nTargetSpacing = 1 * 60;        // Hempcoin: 1 minutes
        bnProofOfWorkLimit = ~uint256(0) >> 1;
        genesis.nTime = 1528499522;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1;
        nDefaultPort = 51436;
        
        hashGenesisBlock = genesis.GetHash();

        if (regenerate) {
            hashGenesisBlock = uint256S("");
            genesis.nNonce = 0;
            if (true && (genesis.GetHash() != hashGenesisBlock)) {
                while (genesis.GetHash() > bnProofOfWorkLimit)
                {
                    ++genesis.nNonce;
                    if (genesis.nNonce == 0)
                    {
                        ++genesis.nTime;
                    }
                }
                std::cout << "// Regtestnet ---";
                std::cout << " nonce: " << genesis.nNonce;
                std::cout << " time: " << genesis.nTime;
                std::cout << " hash: 0x" << genesis.GetHash().ToString().c_str();
                std::cout << " merklehash: 0x"  << genesis.hashMerkleRoot.ToString().c_str() <<  "\n";

            }
        } else {
            LogPrintf("Regtestnet ---\n");
            LogPrintf(" nonce: %u\n", genesis.nNonce);
            LogPrintf(" time: %u\n", genesis.nTime);
            LogPrintf(" hash: 0x%s\n", genesis.GetHash().ToString().c_str());
            LogPrintf(" merklehash: 0x%s\n", genesis.hashMerkleRoot.ToString().c_str());
            assert(hashGenesisBlock == uint256("0x7dc736c75a2c73b92066464ac6bc7cc025e93c52cfa2ff25ee9aaa55509b37a1"));
            assert(genesis.hashMerkleRoot == uint256("0xf81d41745e6e49672fdec6c32ef361b71e5ca817f3d565a037d8398e4a96a33f"));
        }

        vFixedSeeds.clear(); //! Testnet mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Testnet mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fAllowMinDifficultyBlocks = true;
        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;
        fTestnetToBeDeprecatedFieldRPC = false;
    }
    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        return dataRegtest;
    }
};
static CRegTestParams regTestParams;

/**
 * Unit test
 */
class CUnitTestParams : public CMainParams, public CModifiableParams
{
public:
    CUnitTestParams()
    {
        networkID = CBaseChainParams::UNITTEST;
        strNetworkID = "unittest";
        nDefaultPort = 51478;
        vFixedSeeds.clear(); //! Unit test mode doesn't have any fixed seeds.
        vSeeds.clear();      //! Unit test mode doesn't have any DNS seeds.

        fRequireRPCPassword = false;
        fMiningRequiresPeers = false;
        fDefaultConsistencyChecks = true;
        fAllowMinDifficultyBlocks = false;
        fMineBlocksOnDemand = true;
    }

    const Checkpoints::CCheckpointData& Checkpoints() const
    {
        // UnitTest share the same checkpoints as MAIN
        return data;
    }

    //! Published setters to allow changing values in unit test cases
    virtual void setSubsidyHalvingInterval(int anSubsidyHalvingInterval) { nSubsidyHalvingInterval = anSubsidyHalvingInterval; }
    virtual void setEnforceBlockUpgradeMajority(int anEnforceBlockUpgradeMajority) { nEnforceBlockUpgradeMajority = anEnforceBlockUpgradeMajority; }
    virtual void setRejectBlockOutdatedMajority(int anRejectBlockOutdatedMajority) { nRejectBlockOutdatedMajority = anRejectBlockOutdatedMajority; }
    virtual void setToCheckBlockUpgradeMajority(int anToCheckBlockUpgradeMajority) { nToCheckBlockUpgradeMajority = anToCheckBlockUpgradeMajority; }
    virtual void setDefaultConsistencyChecks(bool afDefaultConsistencyChecks) { fDefaultConsistencyChecks = afDefaultConsistencyChecks; }
    virtual void setAllowMinDifficultyBlocks(bool afAllowMinDifficultyBlocks) { fAllowMinDifficultyBlocks = afAllowMinDifficultyBlocks; }
    virtual void setSkipProofOfWorkCheck(bool afSkipProofOfWorkCheck) { fSkipProofOfWorkCheck = afSkipProofOfWorkCheck; }
};

static CChainParams* pCurrentParams = 0;

const CChainParams& Params()
{
    assert(pCurrentParams);
    return *pCurrentParams;
}

CChainParams& Params(CBaseChainParams::Network network)
{
    switch (network) {
    case CBaseChainParams::MAIN:
        return mainParams;
    case CBaseChainParams::TESTNET:
        return testNetParams;
    case CBaseChainParams::REGTEST:
        return regTestParams;
    default:
        assert(false && "Unimplemented network");
        return mainParams;
    }
}

void SelectParams(CBaseChainParams::Network network)
{
    SelectBaseParams(network);
    pCurrentParams = &Params(network);
}

bool SelectParamsFromCommandLine()
{
    CBaseChainParams::Network network = NetworkIdFromCommandLine();
    if (network == CBaseChainParams::MAX_NETWORK_TYPES)
        return false;

    SelectParams(network);
    return true;
}
