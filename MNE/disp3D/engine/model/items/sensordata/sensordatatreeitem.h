//=============================================================================================================
/**
* @file     sensordatatreeitem.h
* @author   Felix Griesau <felix.griesau@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     Month, Year
*
* @section  LICENSE
*
* Copyright (C) Year, Felix Griesau and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief     sensordatatreeitem class declaration.
*
*/

#ifndef DISP3DLIB_SENSORDATATREEITEM_H
#define DISP3DLIB_SENSORDATATREEITEM_H


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../../../disp3D_global.h"
#include "../common/abstracttreeitem.h"
#include "../measurement/measurementtreeitem.h"
#include <fiff/fiff_types.h>

//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QPointer>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================
namespace FIFFLIB{
    class FiffEvoked;
}

namespace MNELIB{
    class MNEBemSurface;
}

//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE DISP3DLIB
//=============================================================================================================

namespace DISP3DLIB {


//*************************************************************************************************************
//=============================================================================================================
// DISP3DLIB FORWARD DECLARATIONS
//=============================================================================================================

class RtSensorDataWorker;

//=============================================================================================================
/**
* Description of what this class is intended to do (in detail).
*
* @brief Brief description of this class.
*/

class DISP3DNEWSHARED_EXPORT SensorDataTreeItem : public AbstractTreeItem
{
    Q_OBJECT

public:
    typedef QSharedPointer<SensorDataTreeItem> SPtr;            /**< Shared pointer type for sensordatatreeitem. */
    typedef QSharedPointer<const SensorDataTreeItem> ConstSPtr; /**< Const shared pointer type for sensordatatreeitem. */

    //=========================================================================================================
    /**
    * Constructs a sensordatatreeitem object.
    */
    explicit SensorDataTreeItem(int iType = Data3DTreeModelItemTypes::SensorDataItem, const QString& text = "Sensor Data");

    //=========================================================================================================
    /**
    * Default destructor
    */
    ~SensorDataTreeItem();
    //=========================================================================================================
    /**
    * Initializes the rt data item with neccessary information for visualization computations.

    */
    void init(const MatrixX3f &matSurfaceVertColor, const MNELIB::MNEBemSurface &inSurface, const FIFFLIB::FiffEvoked &evoked, const QString sensorType);

    //=========================================================================================================
    /**
    * Adds actual rt data which is streamed by this item's worker thread item. In order for this function to worker, you must call init(...) beforehand.
    *
    * @param[in] tSensorData    The MNESourceEstimate data.
    */
    void addData(const MatrixXd& tSensorData);

    //=========================================================================================================
    /**
    * Updates the rt data which is streamed by this item's worker thread item.
    *
    * @return                       Returns true if this item is initialized.
    */
    inline bool isDataInit() const;

    //=========================================================================================================
    /**
    * This function sets the loop flag.
    *
    * @param[in] state     Whether to loop the data or not.
    */
    void setLoopState(bool state);

    //=========================================================================================================
    /**
    * This function sets the data streaming.
    *
    * @param[in] state     Whether to stream the data to the display or not.
    */
    void setStreamingActive(bool state);

    //=========================================================================================================
    /**
    * This function sets the time interval for streaming.
    *
    * @param[in] iMSec     The waiting time inbetween samples.
    */
    void setTimeInterval(int iMSec);

    //=========================================================================================================
    /**
    * This function sets the number of averages.
    *
    * @param[in] iNumberAverages     The new number of averages.
    */
    void setNumberAverages(int iNumberAverages);

    //=========================================================================================================
    /**
    * This function sets the colortable type.
    *
    * @param[in] sColortable     The new colortable ("Hot Negative 1" etc.).
    */
    void setColortable(const QString& sColortable);

    //=========================================================================================================
    /**
    * This function set the normalization value.
    *
    * @param[in] vecThresholds     The new threshold values used for normalizing the data.
    */
    void setNormalization(const QVector3D& tresholds);

    //=========================================================================================================
    /**
    * This function gets called whenever the origin of the surface vertex color changed.
    *
    * @param[in] matVertColorLeftHemisphere       The new vertex colors for the left hemisphere.
    * @param[in] matVertColorRightHemisphere      The new vertex colors for the right hemisphere.
    */
    void setColorOrigin(const MatrixX3f& matVertColor);

protected:
    //=========================================================================================================
    /**
    * AbstractTreeItem functions
    */
    void initItem();

    //=========================================================================================================
    /**
    * This function gets called whenever the check/actiation state of the rt data worker changed.
    *
    * @param[in] checkState     The check state of the worker.
    */
    void onCheckStateWorkerChanged(const Qt::CheckState& checkState);

    //=========================================================================================================
    /**
    * This function gets called whenever this item receives new color values for each estimated source.
    *
    * @param[in] sourceColorSamples     The color values for each estimated source for left and right hemisphere.
    */
    void onNewRtData(const MatrixX3f &sensorData);

    //=========================================================================================================
    /**
    * This function gets called whenever the used colormap type changed.
    *
    * @param[in] sColormapType     The name of the new colormap type.
    */
    void onColormapTypeChanged(const QVariant& sColormapType);

    //=========================================================================================================
    /**
    * This function gets called whenever the time interval in between the streamed samples changed.
    *
    * @param[in] iMSec     The new time in milliseconds waited in between each streamed sample.
    */
    void onTimeIntervalChanged(const QVariant &iMSec);

    //=========================================================================================================
    /**
    * This function gets called whenever the normaization value changed. The normalization value is used to normalize the estimated source activation.
    *
    * @param[in] vecThresholds     The new threshold values used for normalizing the data.
    */
    void onDataNormalizationValueChanged(const QVariant &vecThresholds);

    //=========================================================================================================
    /**
    * This function gets called whenever the check/actiation state of the looped streaming state changed.
    *
    * @param[in] checkState     The check state of the looped streaming state.
    */
    void onCheckStateLoopedStateChanged(const Qt::CheckState& checkState);

    //=========================================================================================================
    /**
    * This function gets called whenever the number of averages of the streamed samples changed.
    *
    * @param[in] iNumAvr     The new number of averages.
    */
    void onNumberAveragesChanged(const QVariant& iNumAvr);

    bool                                m_bIsDataInit;                      /**< The init flag. */

    QPointer<RtSensorDataWorker>     m_pSensorRtDataWorker;       /**< The source data worker. This worker streams the rt data to this item.*/

signals:
    //=========================================================================================================
    /**
    * Emit this signal whenever you want to provide newly generated colors from the stream rt data.
    *
    * @param[in] sourceColorSamples     The color values for each estimated source for left and right hemisphere.
    */
    void rtVertColorChanged(const QVariant &vertColors);


};


//*************************************************************************************************************
//=============================================================================================================
// INLINE DEFINITIONS
//=============================================================================================================
inline bool SensorDataTreeItem::isDataInit() const
{
    return m_bIsDataInit;
}

} // namespace DISP3DLIB

#endif // DISP3DLIB_SENSORDATATREEITEM_H
