#include <Rcpp.h>
#include <stdio.h>
#include <Sapid/Sapid.h>

static SpdBoolean       spdOccIsDeclFuncdef(SpdOcc occ);
static SpdBoolean       spdOccIsExpression(SpdOcc occ);

RcppExport SEXP spdFunctionCallList()
{
  SpdConstString  this_program_name;
  SpdModelId      i_mid, p_mid;
  SpdDBId         db_id;
  SpdObjIdArray   prog_buf, file_buf;
  SpdOccArray     decln_buf, call_buf;
  SpdObjId        declr_id, ident_id, call_id;
  int             i, j, k, l;
  SpdString       decl_name, call_name;
  int count = 0;

  SEXP functionVector, declCallVector;
  std::vector<std::vector<std::string> > decl_calls;

  i_mid = spdUseModel(&spdModels[SPD_MID_I_MODEL]);
  p_mid = spdUseModel(&spdModels[SPD_MID_P_MODEL]);

  db_id = spdOpenSDB();

  spdReadDB(i_mid, db_id);
  spdReadDB(p_mid, db_id);

  prog_buf = spdGetObjIdSortedArray("program", NULL, NULL, spdCompareObjIdName);
  for (i = 0; i < prog_buf.size; i++) {
    file_buf = spdGetRelObjSortedArray(prog_buf.id[i], "prog_file", "any", NULL, spdCompareObjIdName);
    for (j = 0; j < file_buf.size; j++) {
      decln_buf = spdGetIncludedOccSortedArray(file_buf.id[j], "declaration", file_buf.id[j], spdOccIsDeclFuncdef, spdCompareOccOffset);
      for (k = 0; k < decln_buf.size; k++) {
        declr_id = spdGetARelObj(decln_buf.occ[k].objectId, "decl_decl", "any");
        ident_id = spdGetARelObj(declr_id, "decl_ident", "any");
        decl_name = spdGetName(ident_id);
        call_buf = spdGetIncludedOccArray(declr_id, "expression", file_buf.id[j], spdOccIsExpression);
        for (l = 0; l < call_buf.size; l++) {
          call_id= spdGetARelObj(call_buf.occ[l].objectId, "expr_expr", "any");
          call_id= spdGetARelObj(call_id, "ident_ref", "expression_id");
          call_name = spdGetName(call_id);
          std::vector<std::string> decl_call;
          decl_call.push_back(decl_name);
          decl_call.push_back(call_name);
          decl_calls.push_back(decl_call);
          count++;
        } 
        spdFreeOccArray(call_buf);
      }
      spdFreeOccArray(decln_buf);
    }
    spdFreeObjIdArray(file_buf);
  }
  spdFreeObjIdArray(prog_buf);
  spdCloseSDB(db_id);
  return Rcpp::wrap(decl_calls); 
}

static SpdBoolean spdOccIsDeclFuncdef(SpdOcc occ)
{
  return (spdGetAttrValInt(occ.objectId, "sort") == DECL_FUNCDEF);
}

static SpdBoolean spdOccIsExpression(SpdOcc occ)
{
  return (spdGetAttrValInt(occ.objectId, "sort") == EXPR_SORT_FUNCCALL);
}
