#pragma once

namespace GenericBoson
{
	class MemField
	{
	public:
		virtual std::string GetName()                             const = 0;
		virtual std::string GetValueString()                      const = 0;
		virtual bool IsKey()                                      const = 0;
		virtual void Bind()                                             = 0;
		virtual bool IsBound()                                    const = 0;
		virtual void Set(const boost::mysql::field_view value)          = 0;

	public:
		enum class FieldState
		{
			None  = 0,
			Bound = 1,
			Key   = 2,
			MAX,
		};
	};
}
