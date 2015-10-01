/*
 The MIT License (MIT)
 
 Copyright (c) 2013 Luka Penger
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#import "LPTextField.h"

@interface LPTextField ()

@end

@implementation LPTextField

- (void) awakeFromNib {
    [self commonInit];
}

- (id)init {
    self = [super init];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit {
    [self addTarget:self action:@selector(textFieldEditingChanged:) forControlEvents:UIControlEventEditingChanged];
    [self addTarget:self action:@selector(textFieldEditingDidEnd:) forControlEvents:UIControlEventEditingDidEnd];
    [self addTarget:self action:@selector(textFieldEditingDidBegin:) forControlEvents:UIControlEventEditingDidBegin];
}

- (void)onEditingChanged:(void (^)(UITextField *uiTextField))block {
    self.editingChangedBlock = block;
}

- (void)textFieldEditingChanged:(id)sender {
    if(_editingChangedBlock) {
        _editingChangedBlock(self);
    }
}

- (void)onEditingDidEnd:(void (^)(UITextField *uiTextField)) block {
    self.editingDidEndBlock = block;
}

- (void)textFieldEditingDidEnd:(id)sender {
    if(_editingDidEndBlock) {
        _editingDidEndBlock(self);
    }
}

- (void)onEditingDidBegin:(void (^)(UITextField *uiTextField)) block {
    self.editingDidBeginBlock = block;
}

- (void)textFieldEditingDidBegin:(id)sender {
    if(_editingDidBeginBlock) {
        _editingDidBeginBlock(self);
    }
}

@end