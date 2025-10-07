namespace GenericBoson
{
	template<typename L_CALLABLE, typename R_CALLABLE, typename RESULT>
	boost::future<RESULT> operator|(boost::future<L_CALLABLE>&& lhs, boost::future<R_CALLABLE>&& rhs)
	{
		return std::forward<L_CALLABLE>(lhs).then(std::forward<R_CALLABLE>(rhs));
	}
}