#ifdef MYSQL_ENABLE

#include "utils.h"
#include "dbwatcher.h"

#include "util.h"
#include "privsend.h"

using namespace std;
static boost::scoped_ptr<ECCVerifyHandle> global_VerifyHandle;

void InitChain()
{
    if(GetBoolArg("-testnet", false))
	{
        SelectParams(CBaseChainParams::TESTNET);
		printf("Info: select TEST net!\n");
	}
    else
	{
        SelectParams(CBaseChainParams::MAIN);
		printf("Info: select MAIN net!\n");
	}

    ECC_Start();
	global_VerifyHandle.reset(new ECCVerifyHandle());
}

int main(int argc, char const *argv[])
{
    /*init*/
    SetFilePath("licensetool.conf");
	LoadConfigFile(mapArgs, mapMultiArgs);
    InitChain();
    InitLog(argv);
    CKey ucenterPrivkey;
    CPubKey ucenterPubkey;
    std::string strUCenterPrivKey = GetArg("-privkey", "");
    if(!strUCenterPrivKey.empty()) {
        if(!privSendSigner.GetKeysFromSecret(strUCenterPrivKey, ucenterPrivkey, ucenterPubkey)) {
            printf("Invalid ulord center private key in the configuration!\n");
            return -1;
        }
    } else {
        printf("You must specify a Ulord Center privkey in the configuration.!\n");
        return -1;
    }

	MysqlConnectInfo * ptrDBInfo = new MysqlConnectInfo(GetArg("-dbhost", "127.0.0.1"),
														GetArg("-dbport", 3306),
														GetArg("-dbuser", "root"),
                                        				GetArg("-dbpwd", "123456"),
                                        				GetArg("-dbname", "mysql"));

    DBWatcher watcher = DBWatcher(ucenterPrivkey, *ptrDBInfo);
    vector<CMstNodeData> vecnode;

    if(argc > 1)
    {
        if("test" == string(argv[1]))
        {
            watcher.SelectMNData(vecnode);
            watcher.UpdateDB(vecnode);
            return 0;
        }
        if("clear" == string(argv[1]))
        {
            watcher.SelectMNData(vecnode);
            for(auto & mn : vecnode) {
                watcher.ClearMNData(mn);
            }
            return 0;
        }
    }

    return 0;
}

#endif // MYSQL_ENABLE
