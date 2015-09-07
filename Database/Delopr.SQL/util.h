#pragma once

struct FieldExchanger
{
	template <typename Data>	
	void DoFieldExchange(CFieldExchange* pFX, Data& data);
};

/**
 * Extract date from record set and place to @data variable
 * Method @Read must be implemented for each data types
 */
struct DataReader
{
	template <typename R, typename T> int Read(R& rs, T& data);
};

/**
 * Convert CBVariant values to C-types
 * @see RecordSet::GetFieldValueT
 */
struct Converter
{
							bool	IsNULL (const CDBVariant& varValue) const { return DBVT_NULL == varValue.m_dwType;}
	/**	Default data converter. For each return value @GetData method must be overriden. */
	template <typename T>	T		GetData(const CDBVariant& varValue) const;// { ASSERT(true); return NULL}; Лучше пусть ругается линковщик вместо ошибки во время выполнения
	template <>				CString	GetData(const CDBVariant& varValue) const { return IsNULL(varValue) ? "" : *varValue.m_pstring;}
	template <>				BOOL	GetData(const CDBVariant& varValue) const { return varValue.m_boolVal;}
	template <>				long	GetData(const CDBVariant& varValue) const { return varValue.m_lVal;}
	template <>				short	GetData(const CDBVariant& varValue) const { return varValue.m_iVal;}
	template <>				float	GetData(const CDBVariant& varValue) const { return varValue.m_fltVal;}	
	template <>				double	GetData(const CDBVariant& varValue) const { return varValue.m_dblVal;}
	template <>		unsigned char	GetData(const CDBVariant& varValue) const { return varValue.m_chVal;}
	template <>	TIMESTAMP_STRUCT	GetData(const CDBVariant& varValue) const { return IsNULL(varValue) ? TIMESTAMP_STRUCT() : *varValue.m_pdate;}
};
