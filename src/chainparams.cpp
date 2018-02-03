// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xb5;
        pchMessageStart[1] = 0x3c;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xe2;
        vAlertPubKey = ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 23450;
        nRPCPort = 23451;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
       

        const char *pszTimestamp = "De les muntanyes venim crusant tot el bovalar 2018/02/02";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char *)pszTimestamp, (const unsigned char *)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1517611445, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1517611445;
        genesis.nBits = 0x1e0ffff0;
        genesis.nNonce = 1812389;

        hashGenesisBlock = genesis.GetHash();
        // printf("genesis.GetHash = %s\n", genesis.GetHash().ToString().c_str());
        // printf("merkle = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x46e5effa6fa34d1876161c4884842854764b0bf8446a9e65377a994e644c1026"));
        assert(genesis.hashMerkleRoot == uint256("0x2cd553ef14afbd1e1fde07ace136612556bd12e450bae7764ed87ce6b0156965"));

        vSeeds.push_back(CDNSSeedData("n0", "159.65.6.12:23450"));
        vSeeds.push_back(CDNSSeedData("n1", "46.101.177.46:23450"));
        vSeeds.push_back(CDNSSeedData("n2", "13.124.125.253:57706"));
        vSeeds.push_back(CDNSSeedData("n3", "138.68.68.149:45532"));
        vSeeds.push_back(CDNSSeedData("n4", "5.189.152.63:23450"));
        vSeeds.push_back(CDNSSeedData("n5", "95.121.49.87:50094"));
        vSeeds.push_back(CDNSSeedData("n6", "46.4.88.116:59634"));
        vSeeds.push_back(CDNSSeedData("n7", "173.249.7.89:50476"));
        vSeeds.push_back(CDNSSeedData("n8", "147.135.130.119:23450"));
        vSeeds.push_back(CDNSSeedData("n9", "79.144.70.55:50626"));
        

        

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 138);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 21);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 145);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 400000;
    }

    virtual const CBlock &GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress> &FixedSeeds() const
    {
        return vFixedSeeds;
    }

  protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CMainParams
{
  public:
    CTestNetParams()
    {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x27;
        pchMessageStart[1] = 0x5c;
        pchMessageStart[2] = 0xd6;
        pchMessageStart[3] = 0xd9;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("");
        nDefaultPort = 23452;
        nRPCPort = 23453;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits = 0x1e0fffff; //504365055 Decimal Number
        genesis.nTime = 1517611445;
        genesis.nNonce = 1812389;

        //    assert(hashGenesisBlock == uint256("0x9acac6c7390427d4c6d658f4b9b520cb8c23977722783172bed3262b7a233cec));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 76);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 192);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params()
{
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
    case CChainParams::MAIN:
        pCurrentParams = &mainParams;
        break;
    case CChainParams::TESTNET:
        pCurrentParams = &testNetParams;
        break;
    default:
        assert(false && "Unimplemented network");
        return;
    }
}

bool SelectParamsFromCommandLine()
{

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    }
    else
    {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
