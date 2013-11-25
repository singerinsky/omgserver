/*
 * IJob.h
 *
 *  Created on: 2012-2-22
 *      Author: gl
 */

#ifndef CJOB_H_
#define CJOB_H_

#include <cstddef>

namespace omg {

class IJob {
public:
	virtual void ExecuteJob()=0;
	virtual ~IJob(){};
};

} /* namespace omg */
#endif /* CJOB_H_ */
