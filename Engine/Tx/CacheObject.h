#pragma once

namespace GenericBoson
{
	class CacheField;

	enum class QueryType
	{
		INSERT,
		UPDATE,
		DELETE
	};

	class CacheObject
	{
	public:
		std::string GetQuery( const QueryType queryType );

	protected:
		virtual auto GetObjectName() const                            -> std::string                        = 0;
		virtual auto GetFieldNames() const                            -> const std::vector<std::string> &   = 0;
		virtual auto GetFieldName(const int32_t fieldEnumValue) const -> std::string                        = 0;
		virtual auto GetField(const std::string& fieldName) const     -> const std::shared_ptr<CacheField>& = 0;
		virtual auto GetField(const int32_t fieldEnumValue) const     -> const std::shared_ptr<CacheField>& = 0;
	};
}
