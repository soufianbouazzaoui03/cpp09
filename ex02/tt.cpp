
#include "PmergeMe.hpp"

PmergeMe::PmergeMe(void) {}

PmergeMe::PmergeMe(PmergeMe const &other)
{
	*this = other;
}

PmergeMe::~PmergeMe(void) {}

PmergeMe &PmergeMe::operator=(PmergeMe const &other)
{
	(void)other;
	return (*this);
}

void PmergeMe::parseInput(int ac, char **av, std::vector<int> &vec, std::deque<int> &deq)
{
	for (int i = 1; i < ac; i++)
	{
		std::string arg = av[i];
		if (!isdigit(arg[0]) && arg[0] != '+')
		{
			std::cerr << "Error" << std::endl;
			exit(EXIT_FAILURE);
		}
		for (size_t j = 1; j < arg.length(); j++)
		{
			if (!isdigit(arg[j]))
			{
				std::cerr << "Error" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		
		int num = std::atoi(av[i]);
		if (num < 0)
		{
			std::cerr << "Error" << std::endl;
			exit(EXIT_FAILURE);
		}
		vec.push_back(num);
		deq.push_back(num);
	}
}

void PmergeMe::printSequence(const std::string &message, const std::vector<int> &vec)
{
	std::cout << message;
	for (size_t i = 0; i < vec.size(); i++)
	{
		std::cout << vec[i] << (i < vec.size() - 1 ? " " : "\n");
	}
}

std::vector<int> generateJacobsthalSequenceVec(int n)
{
	std::vector<int> jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	int next;

	for (int i = 2; ; ++i)
	{
		next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		if (next >= n)
			break;
		jacobsthal.push_back(next);
	}

	return jacobsthal;
}


std::vector<int> insertPendingVec(std::vector<int> &mainChain, std::vector<int> &pending)
{
	std::vector<int> sortedResult = mainChain;
	std::vector<size_t>insertedIndexes;
	std::vector<int> jacobsthal = generateJacobsthalSequenceVec(pending.size());

	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		size_t index = jacobsthal[i] - 1;
		if (index < pending.size())
		{
			int element = pending[index];
			std::vector<int>::iterator pos = std::lower_bound(sortedResult.begin(), sortedResult.end(), element);
			sortedResult.insert(pos, element);
			insertedIndexes.push_back(index);
		}
	}

	for (size_t i = 0; i < pending.size(); i++)
	{
		int element = pending[i];
		if (find(insertedIndexes.begin(), insertedIndexes.end(), i) == insertedIndexes.end())
		{
			std::vector<int>::iterator pos = std::lower_bound(sortedResult.begin(), sortedResult.end(), element);
			sortedResult.insert(pos, element);
		}
	}

	return sortedResult;
}

void PmergeMe::sortVector(std::vector<int> &vec)
{
	if (vec.size() == 1)
		return;

	std::vector<int> largerElements, smallerElements;

	for (size_t i = 0; i < vec.size(); i++)
	{
		if (i == vec.size() - 1)
			smallerElements.push_back(vec[i]);
		else
		{
			int num1 = vec[i], num2 = vec[i + 1];

			if (num1 < num2)
			{
				smallerElements.push_back(num1);
				largerElements.push_back(num2);
			}
			else
			{
				smallerElements.push_back(num2);
				largerElements.push_back(num1);
			}
			i++;
		}
	}

	if (largerElements.size() > 1)
		sortVector(largerElements);

	vec = insertPendingVec(largerElements, smallerElements);
}

std::deque<int> generateJacobsthalSequenceDeq(int n)
{
	std::deque<int> jacobsthal;
	jacobsthal.push_back(1);
	jacobsthal.push_back(3);
	int next;

	for (int i = 2; ; ++i)
	{
		next = jacobsthal[i - 1] + 2 * jacobsthal[i - 2];
		if (next >= n)
			break;
		jacobsthal.push_back(next);
	}

	return jacobsthal;
}

std::deque<int> insertPendingDeq(std::deque<int> &mainChain, std::deque<int> &pending)
{
	std::deque<int> sortedResult = mainChain;
	std::deque<int> jacobsthal = generateJacobsthalSequenceDeq(pending.size());

	std::deque<int> insertedIndexes;

	for (size_t i = 0; i < jacobsthal.size(); i++)
	{
		size_t index = jacobsthal[i] - 1;

		if (index < pending.size())
		{
			std::deque<int>::iterator it = std::lower_bound(sortedResult.begin(), sortedResult.end(), pending[index]);
			sortedResult.insert(it, pending[index]);
			insertedIndexes.push_back(index);
		}
	}
	
	for (size_t i = 0; i < pending.size(); i++)
	{
		if (find(insertedIndexes.begin(), insertedIndexes.end(), i) == insertedIndexes.end())
		{
			std::deque<int>::iterator it = std::lower_bound(sortedResult.begin(), sortedResult.end(), pending[i]);
			sortedResult.insert(it, pending[i]);
		}
	}
	return sortedResult;
}

void PmergeMe::sortDeque(std::deque<int> &deq)
{
	if (deq.size() == 1)
		return;

	std::deque<int> largerElements, smallerElements;

	for (size_t i = 0; i < deq.size(); i++)
	{
		if (i == deq.size() - 1)
		{
			smallerElements.push_back(deq[i]);
		}
		else
		{
			int num1 = deq[i], num2 = deq[i + 1];

			if (num1 < num2)
			{
				smallerElements.push_back(num1);
				largerElements.push_back(num2);
			}
			else
			{
				smallerElements.push_back(num2);
				largerElements.push_back(num1);
			}
			i++;
		}
	}

	if (largerElements.size() > 1)
	{
		sortDeque(largerElements);
	}

	deq = insertPendingDeq(largerElements, smallerElements);
	
}
