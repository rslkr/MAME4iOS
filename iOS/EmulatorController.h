/*
 * This file is part of MAME4iOS.
 *
 * Copyright (C) 2013 David Valdeita (Seleuco)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses>.
 *
 * Linking MAME4iOS statically or dynamically with other modules is
 * making a combined work based on MAME4iOS. Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * In addition, as a special exception, the copyright holders of MAME4iOS
 * give you permission to combine MAME4iOS with free software programs
 * or libraries that are released under the GNU LGPL and with code included
 * in the standard release of MAME under the MAME License (or modified
 * versions of such code, with unchanged license). You may copy and
 * distribute such a system following the terms of the GNU GPL for MAME4iOS
 * and the licenses of the other code concerned, provided that you include
 * the source code of that other code when and as the GNU GPL requires
 * distribution of source code.
 *
 * Note that people who make modified versions of MAME4iOS are not
 * obligated to grant this special exception for their modified versions; it
 * is their choice whether to do so. The GNU General Public License
 * gives permission to release a modified version without this exception;
 * this exception also makes it possible to release a modified version
 * which carries forward this exception.
 *
 * MAME4iOS is dual-licensed: Alternatively, you can license MAME4iOS
 * under a MAME license, as set out in http://mamedev.org/
 */

#import <UIKit/UIKit.h>

#import "Globals.h"
#import "ScreenView.h"
#import "GCDWebUploader.h"
#import <GameController/GameController.h>

@interface UINavigationController (KeyboardDismiss)

- (BOOL)disablesAutomaticKeyboardDismissal;

@end

#if TARGET_OS_IOS
@class DebugView;
@class AnalogStickView;
@class LayoutView;
@class NetplayGameKit;
#endif

@class iCadeView;

#if TARGET_OS_IOS
@interface EmulatorController : UIViewController<GCDWebUploaderDelegate, UIDocumentPickerDelegate>
#elif TARGET_OS_TV
@interface EmulatorController : GCEventViewController<GCDWebUploaderDelegate>
#endif
{

  ScreenView			* screenView;
  UIImageView	    * imageBack;
  UIImageView	    * imageOverlay;
  UIImageView        * imageInfo;
#if TARGET_OS_IOS
  DebugView         * dview;
  AnalogStickView   * analogStickView;
    LayoutView        *layoutView;    
    NetplayGameKit     *netplayHelper;
#endif
  @public UIView	* externalView;

  UIImageView	    * dpadView;
  UIImageView	    * buttonViews[NUM_BUTTONS];

    
  iCadeView         *icadeView;
    

  UIAlertController *menu;
  
  //input rects
  CGRect rInput[INPUT_LAST_VALUE];
    
  //current rect emulation window
  CGRect rScreenView;
    
  //views frames
  CGRect rFrames[FRAME_RECT_LAST_VALUE];

  //buttons & Dpad images & states
  CGRect rDPadImage;
  NSString *nameImgDPad[NUM_DPAD_ELEMENTS];

  CGRect rButtonImages[NUM_BUTTONS];

  NSString *nameImgButton_Press[NUM_BUTTONS];
  NSString *nameImgButton_NotPress[NUM_BUTTONS];
    
  int dpad_state;
  int old_dpad_state;
    
  
  int old_btnStates[NUM_BUTTONS];
    
  //analog stick stuff
  int stick_radio;
  CGRect rStickWindow;
  CGRect rStickArea;
    
  //input debug stuff
  CGRect debug_rects[100];
  int num_debug_rects;
    
  UIButton *hideShowControlsForLightgun;
  BOOL areControlsHidden;

}

- (int *)getBtnStates;

#if TARGET_OS_IOS
- (CGRect *)getInputRects;
- (CGRect *)getButtonRects;
- (UIView *)getButtonView:(int)i;
- (UIView *)getDPADView;
- (UIView *)getStickView;
- (void)getControllerCoords:(int)orientation;
#endif

- (void)getConf;

- (void)startEmulation;

- (void)done:(id)sender;

- (void)removeTouchControllerViews;
- (void)buildTouchControllerViews;

- (void)changeUI;

#if TARGET_OS_IOS
- (void)buildPortraitImageBack;
- (void)buildPortraitImageOverlay;
- (void)buildPortrait;
- (void)buildLandscapeImageBack;
#endif
- (void)buildLandscapeImageOverlay;
- (void)buildLandscape;


- (void)runMenu;
- (void)runExit;
- (void)runPause;
- (void)runServer;
- (void)endMenu;
#if TARGET_OS_IOS
- (void)runImport;
- (void)runExport;
#endif

- (void)handle_DPAD;
- (void)handle_MENU;

- (void)updateOptions;

- (CGRect *)getDebugRects;
- (void)filldebugRects;

- (UIImage *)loadImage:(NSString *)name;
- (FILE *)loadFile:(const char *)name;

- (void)moveROMS;
- (void)playGame:(NSDictionary*)game;
- (void)chooseGame:(NSArray*)games;

#if TARGET_OS_IOS
- (NSSet*)touchesController:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)beginCustomizeCurrentLayout;
- (void)finishCustomizeCurrentLayout;
- (void)resetCurrentLayout;
- (void)adjustSizes;
#endif

@property (readwrite,strong)  UIView *externalView;
@property (readwrite,assign) int dpad_state;
@property (readonly,assign) int num_debug_rects;
@property (readonly,assign) int stick_radio;
@property (readonly,assign) CGRect rStickArea;
@property (assign) CGRect rStickWindow;
@property (assign) CGRect rDPadImage;
#if TARGET_OS_IOS
@property (strong, nonatomic) UIImpactFeedbackGenerator* impactFeedback;
@property (strong, nonatomic) UISelectionFeedbackGenerator* selectionFeedback;
#endif


@end
