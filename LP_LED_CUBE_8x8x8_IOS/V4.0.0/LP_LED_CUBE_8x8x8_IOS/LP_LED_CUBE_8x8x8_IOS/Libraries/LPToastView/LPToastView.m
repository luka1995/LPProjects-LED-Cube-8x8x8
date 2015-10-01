//
//  ALToastView.h
//


#import <QuartzCore/QuartzCore.h>
#import "LPToastView.h"


@interface LPToastView ()

@property (nonatomic, strong) UILabel *textLabel;

- (void)fadeToastOut;

@end

@implementation LPToastView

// Set visibility duration
static const CGFloat kDuration = 2;

// Static toastview queue variable
static LPToastView *toastView;
static BOOL shown;

#pragma mark - Lifecycle

- (id)initWithText:(NSString *)text {
	if ((self = [self initWithFrame:CGRectZero])) {
		// Add corner radius
		self.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:.6];
		self.layer.cornerRadius = 5;
		self.autoresizingMask = UIViewAutoresizingNone;
		self.autoresizesSubviews = NO;
		
		// Init and add label
		_textLabel = [UILabel new];
		_textLabel.text = text;
		_textLabel.font = [UIFont systemFontOfSize:14];
		_textLabel.textColor = [UIColor whiteColor];
		_textLabel.adjustsFontSizeToFitWidth = NO;
		_textLabel.backgroundColor = [UIColor clearColor];
		[_textLabel sizeToFit];
		
		[self addSubview:_textLabel];
		_textLabel.frame = CGRectOffset(_textLabel.frame, 10, 5);
	}
	
	return self;
}


#pragma mark - Public methods

+ (void)toastInView:(UIView *)parentView withText:(NSString *)text withPaddingBottom:(CGFloat)padding {
	// Add new instance to queue
	LPToastView *view = [[LPToastView alloc] initWithText:text];
  
	CGFloat lWidth = view.textLabel.frame.size.width;
	CGFloat lHeight = view.textLabel.frame.size.height;
	CGFloat pWidth = parentView.frame.size.width;
	CGFloat pHeight = parentView.frame.size.height;
	
	// Change toastview frame
	view.frame = CGRectMake((pWidth - lWidth - 20) / 2., pHeight - lHeight - (80+padding), lWidth + 20, lHeight + 10);
	view.alpha = 0.0f;
    
    if(shown==false)
    {
        shown=true;
        toastView=view;

        [parentView addSubview:view];
        [UIView animateWithDuration:.5  delay:0 options:UIViewAnimationOptionAllowUserInteraction
                         animations:^{
                             view.alpha = 1.0;
                         } completion:^(BOOL finished){}];
        
        // Start timer for fade out
        [view performSelector:@selector(fadeToastOut) withObject:nil afterDelay:kDuration];
    }
}

#pragma mark - Private methods

- (void)fadeToastOut {
	// Fade in parent view
    [UIView animateWithDuration:0.3 delay:0 options:UIViewAnimationOptionAllowUserInteraction
     
                     animations:^{
                         self.alpha = 0.f;
                     }
                     completion:^(BOOL finished){
                         [self removeFromSuperview];
                         shown=false;

                         toastView=nil;
                     }];
}

+ (void)removeToastFromView {
    [toastView removeFromSuperview];
}

@end
