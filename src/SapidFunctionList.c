#include <stdio.h>
#include <string.h>
#include <Sapid/Sapid.h>
#include <R.h>
#include <Rdefines.h>

static SpdBoolean       spdOccIsDeclFuncdef(SpdOcc occ);

SEXP spdFunctionDefList()
{
    SpdConstString  this_program_name;
    SpdModelId      i_mid, p_mid;
    SpdDBId         db_id;
    SpdObjIdArray   prog_buf, file_buf;
    SpdOccArray     decln_buf;
    SpdObjId        declr_id, ident_id;
    int             i, j, k, l;
    SpdString       name;
    //char functionList[1000][1000];

    char functionNames[1000][1000];
//    SEXP functionNameSexps[1000];
    SEXP functionVector;

    /* Initialyze. */
//    this_program_name = spdBasename(argv[0]);
//    spdInitialize(this_program_name);

    /* I-modelとP-modeを使う． */
    i_mid = spdUseModel(&spdModels[SPD_MID_I_MODEL]);
    p_mid = spdUseModel(&spdModels[SPD_MID_P_MODEL]);

    /* SDBを開く． */
    db_id = spdOpenSDB();

    /* I-modelとP-modelを読み込む． */
    spdReadDB(i_mid, db_id);
    spdReadDB(p_mid, db_id);

    /* SDB に格納されているprog_idを取得して，名前で整列する． */
    prog_buf = spdGetObjIdSortedArray("program", NULL, NULL,
                                      spdCompareObjIdName);
    for (i = 0; i < prog_buf.size; i++) {
        /* file_idを取得して，名前で整列する． */
        file_buf = spdGetRelObjSortedArray(prog_buf.id[i], "prog_file", "any",
                                           NULL, spdCompareObjIdName);
        for (j = 0; j < file_buf.size; j++) {
            /* ファイル名を表示する． */
            printf("FILE: %s\n", spdGetName(file_buf.id[j]));
            /* 関数定義を取得して，ファイル先頭からの位置で整列する． */
            decln_buf = spdGetIncludedOccSortedArray(file_buf.id[j],
                                                     "declaration",
                                                     file_buf.id[j],
                                                     spdOccIsDeclFuncdef,
                                                     spdCompareOccOffset);
            for (k = 0; k < decln_buf.size; k++) {
                /* 関数名を表示する． */
                declr_id = spdGetARelObj(decln_buf.occ[k].objectId,
                                         "decl_decl", "any");
                ident_id = spdGetARelObj(declr_id, "decl_ident", "any");
                name = spdGetName(ident_id);
                printf("    FUNCDEF: %s\n", name);

//                PROTECT(functionNames[k]=allocVector(STRSXP, strlen(spdGetName(ident_id))));
//                SET_STRING_ELT(functionNames[k], 0, mkChar(spdGetName(ident_id)));
                //printf("%s", spdGetName(ident_id));
                strncpy(functionNames[k], name, strlen(name));
            }
            spdFreeOccArray(decln_buf);
        }
        spdFreeObjIdArray(file_buf);
    }
    spdFreeObjIdArray(prog_buf);
    spdCloseSDB(db_id);

    //PROTECT(ret = allocMatrix(STRSXP, 1, decln_buf.size));
    PROTECT(functionVector = allocVector(STRSXP, decln_buf.size));
    for (i = 0; i < decln_buf.size; i++) {
      SET_STRING_ELT(functionVector, i, mkChar(functionNames[i]));
      printf("%s\n", functionNames[i]);
    }
    UNPROTECT(1);

    return (functionVector);
}

static SpdBoolean spdOccIsDeclFuncdef(SpdOcc occ)
{
    return (spdGetAttrValInt(occ.objectId, "sort") == DECL_FUNCDEF);
}
