
#ifndef PF_FRAG_STRUX_H
#define PF_FRAG_STRUX_H

#include "ut_types.h"
#include "pf_Frag.h"

// pf_Frag_Strux represents structure information (such as a
// paragraph or section) in the document.

class pf_Frag_Strux : public pf_Frag
{
public:
	pf_Frag_Strux();
	virtual ~pf_Frag_Strux();
	
protected:
	UT_uint32				m_vsIndex;	/* which VS[] we are in */
	pt_AttrPropIndex		m_index;	/* index in VS[].m_tableAttrProp to our A/P */
};

#endif /* PF_FRAG_STRUX_H */
