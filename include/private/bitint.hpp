// Jason Brillante "Damdoshi"
// Hanged Bunny Studio 2014-2019
//
// Bibliothèque Lapin

#ifndef			__LAPIN_PRIVATE_BITINT_HPP__
# define		__LAPIN_PRIVATE_BITINT_HPP__

class			BitInt
{
private:
  size_t		bits;
  std::vector<uint8_t>	data;
  bool			overflow;
  bool			is_signed;

  bool			GetBit(size_t				i) const
  {
    if (i >= bits)
      return (false);
    return ((data[i >> 3] >> (i & 0x07)) & 1);
  }
  void			SetBit(size_t				i,
			       bool				v)
  {
    if (i >= bits)
      return ;
    if (v)
      data[i >> 3] |= 1 << (i & 0x07);
    else
      data[i >> 3] &= ~(1 << (i & 0x07));
  }

public:
  void			Resize(size_t				i)
  {
    bits = i;
    data.resize(bits >> 3, 0);
  }
  bool			Overflow(void) const
  {
    return (overflow);
  }

  BitInt		operator+(const BitInt			&o)
  {
    size_t		maxlen = bits > o.bits ? bits : o.bits;
    bool		carry = false;
    BitInt		n(maxlen);

    for (int i = 0; i < maxlen; ++i)
      {
	bool		l = GetBit(i);
	bool		r = o.GetBit(i);

	if (carry)
	  {
	    if (l && r)
	      n.SetBit(i, true);
	    else if (!l && !r)
	      {
		n.SetBit(i, true);
		carry = false;
	      }
	  }
	else
	  {
	    if (l && r)
	      carry = true;
	    else if (l != r)
	      n.SetBit(i, true);
	  }
      }
    overflow = carry;
    return (n);
  }
  BitInt		operator-(const BitInt			&o)
  {
  }
  BitInt		operator*(const BitInt			&o)
  {
  }
  BitInt		operator/(const BitInt			&o)
  {
  }
  operator		std::string(void) const
  {
  }

  BitInt		operator=(const std::string		&o)
  {
  }
  BitInt		operator=(int				v)
  {
  }

  BitInt(size_t		b,
	 bool		sign)
    : is_signed(sign)
  {
    Resize(b);
  }
  ~BitInt(void);
};

#endif	//		__LAPIN_PRIVATE_BITINT_HPP__
