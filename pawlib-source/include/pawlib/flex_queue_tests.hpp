/** Tests for FlexQueue[PawLIB]
  * Version: 1.0
  *
  * Author(s): Jason C. McDonald, Jonathan Theodore
  */

/* LICENSE
 * Copyright (c) 2016-2019 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#ifndef PAWLIB_FLEXQUEUE_TESTS_HPP
#define PAWLIB_FLEXQUEUE_TESTS_HPP

#include <queue>

#include "pawlib/goldilocks.hpp"
#include "pawlib/flex_queue.hpp"

namespace pawlib
{
    // P-tB1201*
    class TestSQueue_Push : public Test
    {
        private:
            unsigned int iters;

        public:
           explicit TestSQueue_Push(unsigned int iterations): iters(iterations){}

            testdoc_t get_title()
            {
                return "FlexQueue: Push " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }

            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers to a std::vector.";
            }

            bool run()
            {
                // Create instance of queue.
                // Technically we must use vector as a queue!
                ////std::queue<unsigned int> sq;
                std::vector<unsigned int> sq;

                // Push each required element to the queue.
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.push_back(i);
                    if(sq.back() != i)
                    {
                        return false;
                    }
                }
                return true;
            }

            bool run_optimized()
            {
                // Create instance of queue.
                // Technically we must use vector as a queue!
                ////std::queue<unsigned int> sq;
                std::vector<unsigned int> sq;

                // Push each required element to the queue.
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.push_back(i);
                }
                return true;
            }

            ~TestSQueue_Push(){}
    };

    // P-tB1201, P-tS1201
    class TestFQueue_Push : public Test
    {
        private:
            unsigned int iters;

        public:
            explicit TestFQueue_Push(unsigned int iterations)
                :iters(iterations)
                {}


            testdoc_t get_title()
            {
                return "FlexQueue: Push " + stdutils::itos(iters, 10) + " Integers (FlexQueue)";
            }

            testdoc_t get_docs()
            {
                return "Push " + stdutils::itos(iters, 10) + " integers to a FlexQueue.";
            }

            bool run()
            {
                // Create an instance of FlexQueue.
                pawlib::FlexQueue<unsigned int> fq;

                // Push each required element.
                for(unsigned int i=0; i<iters; ++i)
                {
                    // Attempt a push. If it fails...
                    if(!fq.push(i))
                    {
                        // Report failure.
                        return false;
                    }
                    // If last value is not what was pushed...
                    if(fq.peek() != i)
                    {
                        // Report failure.
                    }
                }
                return true;
            }

            bool run_optimized()
            {
                // Create an instance of FlexQueue.
                pawlib::FlexQueue<unsigned int> fq;

                // Push each required element.
                for(unsigned int i=0; i<iters; ++i)
                {
                    fq.push(i);
                }
                return true;
            }

            ~TestFQueue_Push(){}
    };

    // P-tB1202
    class TestFQueue_Peek : public Test
    {
        private:
            pawlib::FlexQueue<int> fq;

        public:
            TestFQueue_Peek(){}

            testdoc_t get_title()
            {
                return "FlexQueue: Peek";
            }

            testdoc_t get_docs()
            {
                return "Peek the first of five integers placed into a FlexQueue";
            }

            //Set up for the test.
            bool pre()
            {
                /* We should set up only once, even if test is repeated
                 * multiple times. */
                for(int i=1; i<=5; ++i)
                {
                    fq.push(i);
                }
                return true;
            }

            bool run()
            {
                // Peek the value.
                int i = fq.peek();

                // If the peeked value is 1, return true; else, false.
                return (i==1);
            }

            ~TestFQueue_Peek(){}
    };

    // P-tB1203*
    class TestSQueue_Pop : public Test
    {
        private:
            /* We must compare against a std::vector, as std::queue doesn't
             * use contiguous memory, and cannot be based on std::vector.
             */
            std::vector<unsigned int> sq;
            unsigned int iters;

        public:
            explicit TestSQueue_Pop(unsigned int iterations)
                :iters(iterations)
                {}

            testdoc_t get_title()
            {
                return "FlexQueue: Pop " + stdutils::itos(iters, 10) + " Integers (std::vector)";
            }

            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers from a std::vector.";
            }

            bool pre()
            {
                return janitor();
            }

            bool janitor()
            {
                // Refill the std::queue
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.push_back(i);
                }
                return true;
            }

            bool run()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.erase(sq.begin());
                }
                return true;
            }

            bool run_optimized()
            {
                for(unsigned int i=0; i<iters; ++i)
                {
                    sq.erase(sq.begin());
                }
                return true;
            }

            ~TestSQueue_Pop(){}
    };

    // P-tB1203, P-tS1203
    class TestFQueue_Pop : public Test
    {
        private:
            pawlib::FlexQueue<unsigned int> fq;
            unsigned int iters;

        public:
            explicit TestFQueue_Pop(unsigned int iterations)
                :iters(iterations)
                {}

            testdoc_t get_title()
            {
                return "FlexQueue: Pop " + stdutils::itos(iters, 10) + " Integers (FlexQueue)";
            }

            testdoc_t get_docs()
            {
                return "Pop " + stdutils::itos(iters, 10) + " integers from a FlexQueue.";
            }

            bool pre()
            {
                return janitor();
            }

            bool janitor()
            {
                // Refill FlexQueue.
                for(unsigned int i=0; i<iters; ++i)
                {
                    fq.push(i);
                }
                return true;
            }

            bool run()
            {
                // Pop each element.
                for(unsigned int i=0; i<iters; ++i)
                {
                    // If the element does not equal the next expected element...
                    if(fq.pop() != i)
                    {
                        // Report failure.
                        return false;
                    }
                }
                return true;
            }

            bool run_optimized()
            {
                // Pop each element.
                for(unsigned int i=0; i<iters; ++i)
                {
                    fq.pop();
                }
                return true;
            }

            ~TestFQueue_Pop(){}
    };

    class TestSuite_FlexQueue : public TestSuite
    {
        public:
            explicit TestSuite_FlexQueue(){}

            void load_tests();

            testdoc_t get_title()
            {
                return "PawLIB: FlexQueue Tests";
            }

            ~TestSuite_FlexQueue(){}
    };

}
#endif // PAWLIB_FLEXQUEUE_TESTS_HPP_H
