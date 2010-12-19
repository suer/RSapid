#include <stdio.h>
#include <Sapid/Sapid.h>
void spdUseModel_wrapper(int *modelId, int *ret)
{
    SpdDBModel *dbmodel;
    switch (*modelId) {
       case 1:
        dbmodel = &spdModels[SPD_MID_I_MODEL];
        break;
       case 2:
        dbmodel = &spdModels[SPD_MID_P_MODEL];
        break;
    }
    printf("%d %d\n",*modelId, dbmodel);
    *ret = spdUseModel(dbmodel);
}
