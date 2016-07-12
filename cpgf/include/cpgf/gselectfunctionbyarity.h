#ifndef __GSELECTFUNCTIONBYARITY_H
#define __GSELECTFUNCTIONBYARITY_H


#include "cpgf/gcompiler.h"
#include "cpgf/gconfig.h"
#include "cpgf/gpp.h"


#define MEMBER_FUNCTIONEXTRACT_HELPER_CV(N, CC, CV) \
	template <typename RT, typename OT GPP_COMMA_IF(N) GPP_REPEAT(N, GPP_COMMA_PARAM, typename P) > \
	RT (CC OT::* GPP_CONCAT(selectFunctionByArity, N)(RT (CC OT::* func ) (GPP_REPEAT_PARAMS(N, P)) CV) )(GPP_REPEAT_PARAMS(N, P)) CV { \
		return func; }

#define MEMBER_FUNCTIONEXTRACT_HELPER(N, CC) \
	MEMBER_FUNCTIONEXTRACT_HELPER_CV(N, CC, GPP_EMPTY()) \
	MEMBER_FUNCTIONEXTRACT_HELPER_CV(N, CC, const) \
	MEMBER_FUNCTIONEXTRACT_HELPER_CV(N, CC, volatile) \
	MEMBER_FUNCTIONEXTRACT_HELPER_CV(N, CC, const volatile)

#define MEMBER_FUNCTIONEXTRACT(CC) \
	GPP_REPEAT_2(G_MAX_ARITY, MEMBER_FUNCTIONEXTRACT_HELPER, CC)

#define GLOBAL_FUNCTIONEXTRACT_HELPER(N, CC) \
	template <typename RT GPP_COMMA_IF(N) GPP_REPEAT(N, GPP_COMMA_PARAM, typename P) > \
	RT (CC * GPP_CONCAT(selectFunctionByArity, N)(RT (CC * func ) (GPP_REPEAT_PARAMS(N, P))) )(GPP_REPEAT_PARAMS(N, P)) { \
		return func; }

#define GLOBAL_FUNCTIONEXTRACT(CC) \
	GPP_REPEAT_2(G_MAX_ARITY, GLOBAL_FUNCTIONEXTRACT_HELPER, CC)

namespace cpgf {

MEMBER_FUNCTIONEXTRACT(GPP_EMPTY())
#ifdef G_SUPPORT_STDCALL
	MEMBER_FUNCTIONEXTRACT(__stdcall)
#endif
#ifdef G_SUPPORT_FASTCALL	
	MEMBER_FUNCTIONEXTRACT(__fastcall)
#endif

GLOBAL_FUNCTIONEXTRACT(GPP_EMPTY())
#ifdef G_SUPPORT_STDCALL
	GLOBAL_FUNCTIONEXTRACT(__stdcall)
#endif
#ifdef G_SUPPORT_FASTCALL	
	GLOBAL_FUNCTIONEXTRACT(__fastcall)
#endif



} // namespace cpgf


#undef MEMBER_FUNCTIONEXTRACT_HELPER_CV
#undef MEMBER_FUNCTIONEXTRACT_HELPER
#undef MEMBER_FUNCTIONEXTRACT
#undef GLOBAL_FUNCTIONEXTRACT_HELPER
#undef GLOBAL_FUNCTIONEXTRACT



#endif

