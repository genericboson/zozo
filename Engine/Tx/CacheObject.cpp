#include "PCH.h"

#include <format>

#include "boost/algorithm/string/join.hpp"

#include "CacheField.h"
#include "CacheObject.h"
#include "CacheTx.h"
#include "Types.h"
#include "TxExecutor.h"

namespace GenericBoson
{
	template<typename T>
	CacheObject<T>::CacheObject(CacheTx& tx)
		: m_tx(tx)
	{
	}

	template<typename T>
	template<typename CALLABLE>
	std::string CacheObject<T>::GetFormattedFieldsString(
		bool  (CacheField::*FieldFunc)() const, 
		const CALLABLE& callable)
	{
		const auto& fields = GetFields();

		std::vector<std::string> formattedFields;
		formattedFields.reserve(fields.size());
		for (const auto pField : fields)
		{
			NULL_CONTINUE(pField);
			if (!std::invoke(FieldFunc, *pField))
				continue;
			
			callable(*pField);
		}

		return boost::algorithm::join(formattedFields, ",");
	}
}