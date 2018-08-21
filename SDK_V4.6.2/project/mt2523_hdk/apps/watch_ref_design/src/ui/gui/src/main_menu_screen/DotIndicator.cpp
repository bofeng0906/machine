/* Copyright Statement:
 *
 * (C) 2005-2016  MediaTek Inc. All rights reserved.
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. ("MediaTek") and/or its licensors.
 * Without the prior written permission of MediaTek and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) MediaTek Software
 * if you have agreed to and been bound by the applicable license agreement with
 * MediaTek ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of MediaTek Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT MEDIATEK SOFTWARE RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 */

#include <gui/main_menu_screen/DotIndicator.hpp>
#include <BitmapDatabase.hpp>
#include <assert.h>

DotIndicator::DotIndicator() :
    unselectedDots(touchgfx::EAST),
    numberOfDots(0),
    currentDot(0)
{
    unselectedDots.setXY(0, 0);
    dotHighlighted.setXY(0, 0);

    add(unselectedDots);
    add(dotHighlighted);
}

DotIndicator::~DotIndicator()
{
}

void DotIndicator::setNumberOfDots(uint8_t size)
{
    numberOfDots = size;

    assert(numberOfDots > 0 && "At least one dot is needed");
    assert(numberOfDots <= MAX_SIZE && "Above maximum number of dots");

    unselectedDots.removeAll();
    for (int i = 0; i < numberOfDots; i++) {
        unselectedDots.add(dotNormal[i]);
    }
    // adjust size of container according to the actual bitmaps
    setWidth(unselectedDots.getWidth());
    setHeight(unselectedDots.getHeight());
    setHighlightPosition(currentDot = 0);
}

void DotIndicator::setBitmaps(const touchgfx::Bitmap &normalDot, const touchgfx::Bitmap &highlightedDot)
{
    dotHighlighted.setBitmap(highlightedDot);
    for (int i = 0; i < MAX_SIZE - 1; i++) {
        dotNormal[i].setBitmap(normalDot);
    }
    if (numberOfDots > 0) {
        setNumberOfDots(numberOfDots);
    }
}

void DotIndicator::goRight()
{
    setHighlightPosition(currentDot = (currentDot + 1) % numberOfDots);
}

void DotIndicator::goLeft()
{
    setHighlightPosition(currentDot = (currentDot + numberOfDots - 1) % numberOfDots);
}

void DotIndicator::setHighlightPosition(uint8_t index)
{
    currentDot = index;

    // note that index is unsigned
    if (index < numberOfDots) {
        dotHighlighted.setX(index * dotNormal[0].getWidth());
    }
    invalidate();
}
