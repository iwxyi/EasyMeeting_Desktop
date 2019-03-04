/*******************************************************************************
* Copyright(c) ArcSoft, All right reserved.
*
* This file is ArcSoft's property. It contains ArcSoft's trade secret, proprietary
* and confidential information.
*
* DO NOT DISTRIBUTE, DO NOT DUPLICATE OR TRANSMIT IN ANY FORM WITHOUT PROPER
* AUTHORIZATION.
*
* If you are not an intended recipient of this file, you must not copy,
* distribute, modify, or take any action in reliance on it.
*
* If you have received this file in error, please immediately notify ArcSoft and
* permanently delete the original and any copy of any file and any printout
* thereof.
*********************************************************************************/

#ifndef _ARCSOFT_SDK_FIC_H_
#define _ARCSOFT_SDK_FIC_H_

#include "amcomdef.h"
#include "asvloffscreen.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*******************************************************************************************
	* FIC 版本信息
	*******************************************************************************************/
	typedef struct {
		MPChar Version;									// Version in string form
		MPChar BuildDate;									// Latest build Date
		MPChar CopyRight;									// Copyright
	}AFIC_FSDK_VERSION;

	/*******************************************************************************************
	* FIC FT/FD人脸特征检测
	*******************************************************************************************/
	typedef struct {
		MInt32 nFace;                        // number of faces detected
		MRECT rcFace;                        // The bounding box of face
	} AFIC_FSDK_FACERES, *LPAFIC_FSDK_FACERES;


	/************************************************************************
	* 激活SDK
	************************************************************************/

	MRESULT ArcSoft_FIC_Activate(
		MPChar APPID,										// [in] APPID
		MPChar SDKKEY 									// [in] SDKKEY
		);

	/************************************************************************
	* 初始化引擎
	************************************************************************/
	MRESULT	ArcSoft_FIC_InitialEngine(
		MHandle	* phFICEngine								// [out] FIC 引擎Handle的指针
		);

	/************************************************************************
	* 人脸特征提取
	************************************************************************/
	MRESULT ArcSoft_FIC_FaceDataFeatureExtraction(
		MHandle hFICEngine,								// [in]  FIC 引擎Handle
		MBool isVideo, 									// [in]  人脸数据类型 1-视频 0-静态图片
		LPASVLOFFSCREEN pInputFaceData,					// [in]  人脸图像原始数据
		LPAFIC_FSDK_FACERES pFaceRes						// [out] 人脸属性 人脸数/人脸框/角度
		);

	/************************************************************************
	* 证件照特征提取
	************************************************************************/
	MRESULT ArcSoft_FIC_IdCardDataFeatureExtraction(
		MHandle hFICEngine,                					// [in]  FIC 引擎Handle
		LPASVLOFFSCREEN pInputIdcardData      					// [in]  图像原始数据
		);

	/************************************************************************
	* 人证比对
	************************************************************************/
	MRESULT ArcSoft_FIC_FaceIdCardCompare(
		MHandle hFICEngine,                				// [in]  FIC 引擎Handle
		MFloat threshold,									// [in]  比对阈值
		MFloat * pSimilarScore,							// [out] 比对结果相似度
		MInt32 * pResult									// [out] 比对结果
		);

	/************************************************************************
	* 释放引擎
	************************************************************************/
	MRESULT ArcSoft_FIC_UninitialEngine(
		MHandle hFICEngine           						// [in]  FIC 引擎Handle
		);

	/************************************************************************
	* 获取版本信息
	************************************************************************/
	const AFIC_FSDK_VERSION *ArcSoft_FIC_GetVersion(MHandle hFICEngine);

#ifdef __cplusplus
}
#endif
#endif