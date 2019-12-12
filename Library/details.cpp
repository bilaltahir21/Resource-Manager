#include "details.h"

details::details()
{
}

details::details(const int id, const int pri, const std::string& acc)
{
	user_id = id;
	priority = pri;
	access = acc;
}

bool details::operator!=(const details obj) const
{
	return user_id != obj.user_id;
}

bool details::operator==(const details obj) const
{
	return user_id == obj.user_id;
}

bool details::operator<(const details obj) const
{
	return user_id < obj.user_id;
}

bool details::operator>(const details obj) const
{
	return user_id > obj.user_id;
}