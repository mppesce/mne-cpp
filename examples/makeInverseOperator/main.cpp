//=============================================================================================================
/**
* @file     main.cpp
* @author   Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     July, 2012
*
* @section  LICENSE
*
* Copyright (C) 2012, Christoph Dinh and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of the Massachusetts General Hospital nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MASSACHUSETTS GENERAL HOSPITAL BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    Implements the main() application function.
*
*/

//*************************************************************************************************************
//=============================================================================================================
// MNE INCLUDES
//=============================================================================================================

#include <fiff/fiff_cov.h>
#include <mne/mne.h>


//*************************************************************************************************************
//=============================================================================================================
// STL INCLUDES
//=============================================================================================================

#include <math.h>
#include <iostream>


//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtCore/QCoreApplication>


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace FIFFLIB;
using namespace MNELIB;


//*************************************************************************************************************
//=============================================================================================================
// MAIN
//=============================================================================================================

//=============================================================================================================
/**
* The function main marks the entry point of the program.
* By default, main has the storage class extern.
*
* @param [in] argc (argument count) is an integer that indicates how many arguments were entered on the command line when the program was started.
* @param [in] argv (argument vector) is an array of pointers to arrays of character objects. The array objects are null-terminated strings, representing the arguments that were entered on the command line when the program was started.
* @return the value that was set to exit() (which is 0 if exit() is called via quit()).
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile t_fileFwdMeeg("./MNE-sample-data/MEG/sample/sample_audvis-meg-eeg-oct-6-fwd.fif");
    QFile t_fileFwdEeg("./MNE-sample-data/MEG/sample/sample_audvis-eeg-oct-6-fwd.fif");
    QFile t_fileCov("./MNE-sample-data/MEG/sample/sample_audvis-cov.fif");
    QFile t_fileEvoked("./MNE-sample-data/MEG/sample/sample_audvis-ave.fif");

    double snr = 3.0;
    double lambda2 = 1.0 / pow(snr, 2);

    // Load data
    fiff_int_t setno = 0;
    FiffEvokedDataSet evoked(t_fileEvoked, setno);
    MNEForwardSolution t_forwardMeeg;
    if(!MNEForwardSolution::read_forward_solution(t_fileFwdMeeg, t_forwardMeeg))
    {
        printf("Forward solution not found: %s\n", t_fileFwdMeeg.fileName().toLatin1().constData());
        return 0;
    }
    FiffCov noise_cov(t_fileCov);

    qDebug() << "Dimensions: " << noise_cov.data.rows() << " x " << noise_cov.data.cols();


    return a.exec();
}