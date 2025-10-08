namespace GenericBoson
{
	template<typename L_FUTURE, typename R_CALLABLE>
	void operator|(L_FUTURE&& lhs, R_CALLABLE&& rhs)
	{
		std::forward<L_FUTURE>(lhs).then(std::forward<R_CALLABLE>(rhs));
	}
}