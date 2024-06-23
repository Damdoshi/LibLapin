
static size_t	_rstrlen(const char				*str,
			 size_t					len)
{
  return (*str ? strlen(str + 1, len + 1) : len);
}

size_t		$([].Prefix)strlen$([].Suffix)(const char	*str)
{
  return (_rstrlen(str, 0));
}

