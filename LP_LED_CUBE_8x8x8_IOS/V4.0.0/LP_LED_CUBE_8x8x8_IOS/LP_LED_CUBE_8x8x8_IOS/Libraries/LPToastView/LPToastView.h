//
//  LPToastView.h
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>


@interface LPToastView : UIView

+ (void)toastInView:(UIView *)parentView withText:(NSString *)text withPaddingBottom:(CGFloat)padding;
+ (void)removeToastFromView;

@end
