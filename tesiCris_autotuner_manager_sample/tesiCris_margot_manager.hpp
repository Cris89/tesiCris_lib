#ifndef TESICRIS_MARGOTMANAGER_HPP
#define TESICRIS_MARGOTMANAGER_HPP

#include <iostream>
#include <string>
#include <vector>

#include <margot.hpp>
#include <tesiCris/framework.hpp>

class tesiCris_Margot_Manager
{
public:
	tesiCris_Margot_Manager();

	void init();

	void updateOPs();

	void sendResult( std::vector<float> params, std::vector<float> metrics );

	virtual ~tesiCris_Margot_Manager();

private:
	Framework *tesiCris_framework;
};

#endif
